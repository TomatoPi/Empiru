/*
 * Copyright (C) 2020 DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/// 
/// \file   RenderingEngine.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 10 septembre 2020, 14:56
/// \brief Core object of rendering engine
///
#include <render/impl/REngine.h>
#include <log/log.h>
#include <cassert>

namespace render {

IAllocator *IAllocator::_allocator = nullptr;
IREngine *IREngine::_instance = nullptr;

namespace impl {

AssetUIDGen REngine::assetUIDGen = AssetUIDGen();

REngine::REngine(PixelPerfectBridge &bridge, gui::Viewport &view,
    world::IMap &world) noexcept :
    _bridge(bridge), _view(view), _world(world), _allocs(), _assets(), _objects(), _garbage(), _stack(), _tiles(), _updateList(), _tileTarget(), _dirtyStack(
        true) {
  /* subscribe to viewport events */
  _view.gui::Viewport::Subject<gui::Events::ViewportMoved>::addSubscriber( // @suppress("Method cannot be resolved")
      [this](gui::Viewport&, gui::Events::ViewportMoved&) -> void {
        _dirtyStack = true;
      });
  _view.gui::Viewport::Subject<gui::Events::ViewportRotated>::addSubscriber( // @suppress("Method cannot be resolved")
      [this](gui::Viewport&, gui::Events::ViewportRotated&) -> void {
        _dirtyStack = true;
      });
  /* subscribe to Bridge events */
  _bridge.PixelPerfectBridge::Subject<render::impl::Events::BridgeNeedUpdate>::addSubscriber( // @suppress("Method cannot be resolved")
      [this](PixelPerfectBridge &bridge,
          render::impl::Events::BridgeNeedUpdate&) -> void {
        bridge.clearTable();
        for (auto [pos, list] : _stack) {
          for (auto ptr : list) {
            bridge.addObject(*ptr, _view);
          }
        }
      });
}

const AssetUID REngine::registerAsset(std::shared_ptr<Asset> asset,
    Allocator *alloc) noexcept {
  AssetUID uid(assetUIDGen.generateUID());
  bool success = _assets.emplace(uid, asset).second; // @suppress("Field cannot be resolved") // @suppress("Method cannot be resolved")
  assert(success);
  success = _allocs.emplace(uid, alloc).second; // @suppress("Field cannot be resolved") // @suppress("Method cannot be resolved")
  assert(success);
  return uid;
}

void REngine::setTileTarget(ATarget *target) noexcept {
  _tileTarget = target;
}

ATarget::Pointer REngine::createObject(ATarget::Builder &builder) {
  /* alloc and build object */
  builder.asset = _assets.at(builder.kind); // @suppress("Method cannot be resolved")
  ATarget::Pointer ptr(_allocs.at(builder.kind)->createObject()); // @suppress("Invalid arguments") // @suppress("Method cannot be resolved")
  builder(*ptr);
  /* subscribe to created object movements */
  ptr->ATarget::Subject<render::Events::TargetMoved>::addSubscriber( // @suppress("Method cannot be resolved")
      [this](ATarget &obj, render::Events::TargetMoved &event) -> void {
        _updateList.emplace_back(obj.ptr());
      });
  /* subscribe to created object destruction */
  ptr->ATarget::Subject<render::Events::TargetDiscarded>::addSubscriber( // @suppress("Method cannot be resolved")
      [this](ATarget &obj, render::Events::TargetDiscarded &event) -> void {
        LOG::debug("Discard render target :", obj.entity());
        removeObject(obj.ptr());
      });
  /* add object */
  addObject(ptr);
  /* notify the world */
  Subject<render::Events::TargetCreated>::notify(ptr); // @suppress("Function cannot be resolved")
  return ptr;
}

void REngine::destroyGarbadge() {
  for (auto &ptr : _garbage) {
    _allocs.at(ptr->kind())->deleteObject(ptr); // @suppress("Method cannot be resolved")
  }
  _garbage.clear();
}

ATarget& REngine::getTarget(const game::EUID uid) noexcept {
  return *_objects[uid];
}

void REngine::addObject(ATarget::Pointer ptr) noexcept {
  _objects.emplace(ptr->entity(), ptr); // @suppress("Method cannot be resolved")
  _updateList.emplace_back(ptr);
}

void REngine::removeObject(ATarget::Pointer ptr) noexcept {
  removeFromStack(ptr);
  _objects.erase(ptr->entity());
  _garbage.emplace(ptr);
}

void REngine::removeFromStack(ATarget::Pointer ptr) noexcept {
  if (auto itr = _stack.find(ptr->viewpos()); itr != _stack.end()) {
    itr->second.erase(ptr);
    if (itr->second.empty()) {
      _stack.erase(itr);
    }
  }
}
void REngine::addToStack(ATarget::Pointer ptr) noexcept {
  if (!_stack.contains(ptr->viewpos())) {
    _stack[ptr->viewpos()] = std::set<ATarget::Pointer, alloc::PtrComp>();
  }
  _stack[ptr->viewpos()].emplace(ptr);
}

void REngine::updateDrawStack() noexcept {
  // Compute anchor position and drawsteps
  hex::Axial anchor(_view.upLeftCorner());
  auto [vx, vy] = _view.viewPortAxis();
  hex::Axial pos;
  // Move one tile away to always draw left and up tiles
  anchor = (anchor - vx * 2 - vy * 2).tile();
  // Compute render situation
  int xx, yy, dx(_view.tileWidth() * 0.9), dy(_view.tileHeight() * 0.9);
  // Clear draw context
  _stack.clear();
  _tiles.clear();
  _updateList.clear();
  // Get initial position and start
  for (xx = -_view.tileWidth() * 2;
      (xx - dx) - _view.tileWidth() < _view.viewWidth();
      xx += dx, anchor = anchor + vx) {
    for (pos = anchor, yy = -_view.tileHeight() * 2;
        (yy - dy) - _view.tileHeight() < _view.viewHeight();
        yy += dy, pos = pos + vy) {
      // Render tile pos at (x, y+offx[!!flip])
      if (_world.isOnMap(pos)) {
        _tiles.emplace_back(_view.toPixel(pos.tile()));
        if (auto vec = _world.getContentAt(pos)) {
          for (const world::Object::Pointer &obj : *vec) {
            ATarget::Pointer ptr(_objects.at(obj->entity())); // @suppress("Invalid arguments") // @suppress("Method cannot be resolved")
            ptr->viewpos(_view.toPixel(ptr->worldpos()), _view.tileSize());
            if (_view.doesIntersect(ptr->blitRect())) {
              addToStack(ptr);
            }
          }
        } //< if content
      } //< if world
    } //< for each row
  } //< for each column
  _dirtyStack = false;
}

void REngine::render() {
  // if stack is dirty recompute it
  if (_dirtyStack) {
    updateDrawStack();
  }
  // Update neededs
  for (ATarget::Pointer &ptr : _updateList) {
    removeFromStack(ptr);
    gui::Pixel pix(_view.toPixel(ptr->worldpos()));
    ptr->viewpos(pix, _view.tileSize());
    if (_view.doesIntersect(ptr->blitRect())) {
      addToStack(ptr);
    }
  }
  _updateList.clear();
  // Draw tiles
  for (auto &tile : _tiles) {
    _tileTarget->viewpos(tile, _view.tileSize()); // @suppress("Invalid arguments")
    _tileTarget->draw();
  }
  // Draw all entities
  for (auto [pos, list] : _stack) {
    for (auto ptr : list) {
      ptr->draw();
    }
  }
}

}  // namespace impl
} /* namespace render */
