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
#include "utils/log.h"

RenderingEngine::RenderingEngine(
    Window &               win,
    const HexViewport &    vp,
    const AbstractCamera & cam,
    const WorldInterface & wo) : 
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
  AbstractRenderer * rdr) 
{
  assert(_renderers.emplace(std::type_index(info), rdr).second);
}

void RenderingEngine::render() {
  FlatHexPosition anchor, pos, vx, vy;
  // Compute anchor position and drawsteps
  _worldView.upLeftCorner(&anchor);
  _worldView.viewPortAxis(&vx, &vy);
  // Move one tile away to always draw left and up tiles
  anchor = anchor - vx*2 - vy*2;
  anchor.toTile();
  // Compute render situation
  int x, y, xx, yy,
      dx(_worldView.tileWidth() * 0.75), 
      dy(_worldView.tileHeight());
  // Get tile renderer
  AbstractRenderer * tilerdr(
        _renderers.find(std::type_index(typeid(Tile)))->second);
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
        _worldView.toPixel(pos.toTile(), &x, &y);
        if (tilerdr->renderAt(nullptr, _camera.getOrientation(), 
            x, y, _worldView, _window.renderer)) 
        {
          LOG_WRN("%s\n", SDL_GetError());
          OUPS();
        }
        
        auto vec(_world.getContentAt(pos));
        if (vec) {
          for (auto & obj : *vec) {
            _worldView.toPixel(obj->pos(), &x, &y);
            _drawstack.emplace(Position(x, y), obj);
          }
        }
      }
    }
  } //< for each tile
  
  // Draw all entities
  for (auto & itr : _drawstack) {
    WorldObject *obj(itr.second);
    // Get correct renderer and use it
    _renderers.find(std::type_index(typeid(*obj)))->second
        ->renderAt(
            obj,
            _camera.getOrientation(), 
            itr.first._x, itr.first._y, _worldView, _window.renderer);
  }
}