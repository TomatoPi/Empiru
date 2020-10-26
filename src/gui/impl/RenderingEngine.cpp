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

#include <cassert>

#include "RenderingEngine.h"
#include "objects/entity/core/Entity.h"

#include "utils/log.h"

namespace gui {
  
  RenderingEngine::RenderingEngine(
      Window&               win,
      const hex::Viewport&  vp,
      const AbstractCamera& cam,
      const IWorldMap& wo) : 
    _window(win),
    _worldView(vp),
    _camera(cam),
    _world(wo),
    _renderers(),
    _drawstack()
  {
  }

  /// \brief Add a new renderer associated with given WorldObject type
  void RenderingEngine::attachRenderer(
    const std::type_info & info, 
    ARenderer * rdr) 
  {
    bool success(_renderers.emplace(std::type_index(info), rdr).second);
    assert(success);
    /* attach related object creation event */
    core::IAllocator::Get().addCreationSubscriber(info, 
        std::bind(&RenderingEngine::newTarget, this, std::placeholders::_1));
    core::IAllocator::Get().addDestructionSubscriber(info, 
        std::bind(&RenderingEngine::targetDeleted, this, std::placeholders::_1));
  }
  
  void RenderingEngine::newTarget(core::Pointer ptr) noexcept {
    using MoveE = decorators::DrawableEvents::WorldPosMoved;
    Target& target(static_cast<Target&>(*ptr));
    target.core::OSubject<MoveE>::addSubscriber(core::Pointer(nullptr), 
        SuperObserver::bindCallback(
          [](RenderingEngine* rdr, const core::OSubject<MoveE>& obj, const MoveE&)
          -> void {
            rdr->_changeds.emplace_back(static_cast<const Target&>(obj).ptr());
          }, this));
  }
  void RenderingEngine::targetDeleted(core::Pointer ptr) noexcept {
    removeFromStack(ptr);
  }
  void RenderingEngine::updateDrawStack() noexcept {
    hex::Axial anchor, pos, vx, vy;
    // Compute anchor position and drawsteps
    _worldView.upLeftCorner(&anchor);
    _worldView.viewPortAxis(&vx, &vy);
    // Move one tile away to always draw left and up tiles
    anchor = hex::Axial(anchor - vx*2 - vy*2).tile();
    // Compute render situation
    int x, y, xx, yy,
        dx(_worldView.tileWidth() * 0.75), 
        dy(_worldView.tileHeight());
    // Clear draw context
    _drawstack.clear();
    _viewables.clear();
    _changeds.clear();
    // Get initial position and start
    for (
        xx = -_worldView.tileWidth() *2;
        (xx-dx) - _worldView.tileWidth() < _window.width;
        xx += dx, anchor = anchor +vx
        )
    {
      for (
          pos = anchor, yy = -_worldView.tileHeight() *2; 
          (yy-dy) - _worldView.tileHeight() < _window.height ;
          yy += dy, pos = pos +vy
          )
      {
        // Render tile pos at (x, y+offx[!!flip])
        if (_world.isOnMap(pos)) {
          _worldView.toPixel(pos.tile(), &x, &y);
          _viewables.emplace_back(x, y);

          auto vec(_world.getContentAt(pos));
          if (vec) {
            for (auto obj : *vec) {
              using WO = decorators::WorldObject;
              Target& target(obj->as<WO>().entity()->as<Target>());
              _worldView.toPixel(target.worldpos(), &x, &y);
              target.viewpos(Pixel(x, y));
              _drawstack.emplace(target.viewpos(), obj);
            }
          }
        }
      }
    } //< for each tile
  }
  void RenderingEngine::removeFromStack(const core::Pointer& ptr) noexcept {
    /* Remove the object from the drawstack if present */
    using Target = decorators::ADrawable;
    const Target& target(static_cast<const Target&>(*ptr));
    std::set<core::Pointer,alloc::PtrComp> backup(_drawstack.count(target.viewpos()));
    while (auto itr = _drawstack.find(target.viewpos())) {
      backup.emplace(itr->second);
      _drawstack.erase(itr);
    }
    backup.erase(ptr);
    for (auto& obj : backup) {
      _drawstack.emplace(target.viewpos(), obj);
    }
  }

  /// \brief renturn the renderer for specified type 
  ///   or throw if type not registered
  ARenderer * RenderingEngine::getrdr(const core::Pointer& obj) {
    return _renderers.at(std::type_index(typeid(*obj)));
  }

  void RenderingEngine::render() {
    // Update neededs
    for (auto ptr : _changeds) {
      Target& target(ptr->as<Target>());
      removeFromStack(ptr);
      int x, y;
      _worldView.toPixel(target.worldpos(), &x, &y);
      target.viewpos(Pixel(x, y));
      _drawstack.emplace(target.viewpos(), ptr);
    }
    _changeds.clear();
    // Draw tiles 
    ARenderer* tilerdr(_renderers.at(std::type_index(typeid(Tile))));
    for (auto & tile : _viewables) {
      try {
        tilerdr->renderAt(core::Pointer(nullptr), _camera.getOrientation(), 
          tile._x, tile._y, _worldView);
      } catch (const std::exception & e) {
        LOG_ERROR("Failed draw tile : %s\n", SDL_GetError());
        throw;
      }
    }
    // Draw all entities
    for (auto& itr : _drawstack) {
      // Get correct renderer and use it
      getrdr(itr.second)->renderAt(
            itr.second,
            _camera.getOrientation(), 
            itr.first._x, itr.first._y,
            _worldView);
    }
  }

  /// \brief Draw every sized object 
  void RenderingEngine::updateClickZones() {
    // Clear the mask
    SDL_SetRenderDrawColor(_window.vrenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(_window.vrenderer);
    // Iniitalise unique colors
    _colors.clear();
    uint32_t cptr(1);
    // Draw is made according to last drawstack
    for (auto & itr : _drawstack) {
      SDL_Color color;
      color.r = (cptr & 0x000000FF) >> 0;
      color.g = (cptr & 0x0000FF00) >> 8;
      color.b = (cptr & 0x00FF0000) >> 16;
      color.a = 255;
      // Get correct renderer and use it
      getrdr(itr.second)->renderAt(
          itr.second,
          _camera.getOrientation(), 
          itr.first._x, itr.first._y,
          _worldView, color);
      _colors.emplace(color, entity);
      cptr += 1;
    }
  }

  core::Pointer RenderingEngine::entityAt(int x, int y) const noexcept {
    SDL_LockSurface(_window.vsurface);
    SDL_Color color{255, 255, 255, 255};
    SDL_GetRGB(
        static_cast<uint32_t*>(_window.vsurface->pixels)
          [y * _window.vsurface->w + x],
        _window.vsurface->format,
        &color.r, &color.g, &color.b);
    SDL_UnlockSurface(_window.vsurface);
    //LOG_DEBUG("Click at : %d,%d : color : %d,%d,%d\n", x, y, color.r, color.g, color.b);
    auto itr(_colors.find(color));
    if (itr != _colors.end()) {
      //LOG_DEBUG("OBJ : %s\n", typeid(**(itr->second)).name());
      return itr->second;
    }
    //LOG_DEBUG("NOTHING\n");
    return core::Pointer(nullptr);
  }
}