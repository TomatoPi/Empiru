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
#include <cassert>

namespace render {

IAllocator *IAllocator::_allocator = nullptr;

namespace impl {

AssetUIDGen REngine::assetUIDGen = AssetUIDGen();

REngine::REngine(PixelPerfectBridge &bridge, gui::Viewport &view,
    world::IMap &world) noexcept :
    _bridge(bridge), _view(view), _world(world), _allocs(), _assets(), _objects(), _garbage(), _stack(), _tiles(), _updateList(), _tileTarget(), _dirtyStack(
        true) {
}

void REngine::bindSignals() noexcept {
  /* subcribe to object creations */
  IAllocator::Get().Subject<render::Events::TargetCreated>::addSubscriber(
      [this](IAllocator&, render::Events::TargetCreated &event) -> void {
        /* subscribe to created object movements */
        event.ptr->ATarget::Subject<render::Events::TargetMoved>::addSubscriber(
            [this](ATarget &obj, render::Events::TargetMoved &event) -> void {
              _updateList.emplace_back(obj.ptr());
            });
        /* subscribe to created object destruction */
        event.ptr->ATarget::Subject<render::Events::TargetDiscarded>::addSubscriber(
            [this](ATarget &obj,
                render::Events::TargetDiscarded &event) -> void {
              removeObject(obj.ptr());
            });
        /* add object */
        this->addObject(event.ptr);
      });
  /* subscribe to viewport events */
  _view.gui::Viewport::Subject<gui::Events::ViewportMoved>::addSubscriber(
      [this](gui::Viewport&, gui::Events::ViewportMoved&) -> void {
        _dirtyStack = true;
      });
  _view.gui::Viewport::Subject<gui::Events::ViewportRotated>::addSubscriber(
      [this](gui::Viewport&, gui::Events::ViewportRotated&) -> void {
        _dirtyStack = true;
      });
  /* subscribe to Bridge events */
  _bridge.PixelPerfectBridge::Subject<render::impl::Events::BridgeNeedUpdate>::addSubscriber(
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
  bool success = _assets.emplace(uid, asset).second;
  assert(success);
  success = _allocs.emplace(uid, alloc).second;
  assert(success);
  return uid;
}

void REngine::setTileTarget(ATarget *target) noexcept {
  _tileTarget = target;
}

ATarget::Pointer REngine::createObject(AssetUID kind,
    ATarget::Builder &builder) {
  builder.asset = _assets.at(kind);
  builder.kind = kind;
  ATarget::Pointer ptr(_allocs.at(kind)->createObject());
  builder(ptr);
  Subject<render::Events::TargetCreated>::notify(ptr);
  return ptr;
}

void REngine::destroyGarbadge() {
  for (auto &ptr : _garbage) {
    _allocs.at(ptr->kind())->deleteObject(ptr);
  }
}

void REngine::addObject(ATarget::Pointer ptr) noexcept {
  _objects.emplace(ptr->entity(), ptr);
  _updateList.emplace_back(ptr);
}

void REngine::removeObject(ATarget::Pointer ptr) noexcept {
  removeFromStack(ptr);
  _garbage.emplace_back(ptr);
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
  int xx, yy, dx(_view.tileWidth() * 0.75), dy(_view.tileHeight());
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

        auto vec(_world.getContentAt(pos));
        if (vec) {
          for (const world::Object::Pointer &obj : *vec) {
            ATarget::Pointer ptr(_objects.at(obj->entity()));
            ptr->viewpos(_view.toPixel(ptr->worldpos()));
            addToStack(ptr);
          }
        }
      }
    }
  } //< for each tile
}

void REngine::render() {
  // Update neededs
  for (ATarget::Pointer &ptr : _updateList) {
    removeFromStack(ptr);
    ptr->viewpos(_view.toPixel(ptr->worldpos()));
    addToStack(ptr);
  }
  _updateList.clear();
  // Draw tiles
  for (auto &tile : _tiles) {
    _tileTarget->viewpos(tile);
    _tileTarget->draw(_view);
  }
  // Draw all entities
  for (auto [pos, list] : _stack) {
    for (auto ptr : list) {
      ptr->draw(_view);
    }
  }
}

}  // namespace impl
} /* namespace render */
