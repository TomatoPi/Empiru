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
#include "events/ControllerEvents.h"
#include "events/GameEvents.h"

#include "utils/log.h"

RenderingEngine::RenderingEngine(
    Window &               win,
    const hex::Viewport &  vp,
    const AbstractCamera & cam,
    const WorldInterface & wo) : 
  _window(win),
  _worldView(vp),
  _camera(cam),
  _world(wo),
  _renderers(),
  _drawstack()
{
  this->registerEvent<EventObjectSelected>(
      [this](const EventObjectSelected & event) -> void {
        getrdr(event._obj)->targetSelected(event._obj);
      });
  this->registerEvent<EventObjectDeselected>(
      [this](const EventObjectDeselected & event) -> void {
        getrdr(event._obj)->targetDeselected(event._obj);
      });
  this->registerEvent<EventObjectCreated>(
      [this](const EventObjectCreated & event) -> void{
        getrdr(event._obj)->addTarget(event._obj);
      });
  this->registerEvent<EventObjectDestroyed>(
      [this](const EventObjectDestroyed & event) -> void{
        getrdr(event._obj)->addTarget(event._obj);
      });
}

/// \brief Add a new renderer associated with given WorldObject type
void RenderingEngine::attachRenderer(
  const std::type_info & info, 
  AbstractRenderer * rdr) 
{
  bool success(_renderers.emplace(std::type_index(info), rdr).second);
  assert(success);
}

/// \brief renturn the renderer for specified type 
///   or throw if type not registered
AbstractRenderer * RenderingEngine::getrdr(const WorldRef * obj) {
  return _renderers.at(std::type_index(typeid(**obj)));
}

void RenderingEngine::render() {
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
  // Get tile renderer
  AbstractRenderer * tilerdr(_renderers.at(std::type_index(typeid(Tile))));
  _drawstack.clear();
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
        try {
          tilerdr->renderAt(nullptr, _camera.getOrientation(), 
            x, y, _worldView, _window.renderer);
        } catch (const std::exception & e) {
          LOG_ERROR("Failed draw tile : %s\n", SDL_GetError());
          throw;
        }
        
        auto vec(_world.getContentAt(pos));
        if (vec) {
          for (auto & obj : *vec) {
            _worldView.toPixel((**obj).pos(), &x, &y);
            _drawstack.emplace(Pixel(x, y), obj);
          }
        }
      }
    }
  } //< for each tile
  
  // Draw all entities
  for (auto & itr : _drawstack) {
    const WorldRef * obj(itr.second);
    // Get correct renderer and use it
    try {
      getrdr(obj)->renderAt(
            obj,
            _camera.getOrientation(), 
            itr.first._x, itr.first._y,
            _worldView, _window.renderer);
    } catch (const std::exception & e) {
      LOG_ERROR("Failed draw object : %s\n", e.what());
      throw;
    }
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
    WorldRef * obj(itr.second);
    if ((**obj).sizeClass() == WorldObject::SHollow) {
      continue;
    }
    SDL_Color color;
    color.r = (cptr & 0x000000FF) >> 0;
    color.g = (cptr & 0x0000FF00) >> 8;
    color.b = (cptr & 0x00FF0000) >> 16;
    color.a = 255;
    // Get correct renderer and use it
    try {
      getrdr(obj)->renderAt(
          obj,
          _camera.getOrientation(), 
          itr.first._x, itr.first._y,
          _worldView, _window.vrenderer,
          color);
    } catch (const std::exception & e) {
      LOG_ERROR("Failed draw object : %s\n", e.what());
      throw;
    }
    _colors.emplace(color, obj);
    cptr += 1;
  }
}

WorldRef * RenderingEngine::objectAt(int x, int y) const noexcept {
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
  return nullptr;
}