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
/// \file   WorldRenderer.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 10 septembre 2020, 14:56
///

#include <cassert>

#include "RenderingEngine.h"
#include "utils/log.h"

RenderingEngine::RenderingEngine(
    Window *w, 
    HexViewport *c, 
    AbstractCamera *ac,
    World *wo, 
    AbstractRenderer *t,
    AbstractRenderer *p) : 
  _window(w),
  _worldView(c),
  _camera(ac),
  _world(wo),
  _tilerdr(t),
  _peonrdr(p)
{
  assert(w);
  assert(c);
  assert(t);
  assert(wo);
  assert(p);
}

void RenderingEngine::render() {
  FlatHexPosition anchor, pos, vx, vy;
  // Compute anchor position and drawsteps
  _worldView->upLeftCorner(&anchor);
  _worldView->viewPortAxis(&vx, &vy);
  // Move one tile away to always draw left and up tiles
  //LOG_DEBUG("=============================\n");
  //LOG_DEBUG("%s\n", anchor.toString().c_str());
  anchor = anchor - vx - vy;
  //LOG_DEBUG("%s\n", anchor.toString().c_str());
  anchor.tile();
  //LOG_DEBUG("%s\n", anchor.toString().c_str());
  // Compute render situation
  int x, y, xx, yy,
      dx(_worldView->tileWidth() * 0.75), 
      dy(_worldView->tileHeight());
  // Get initial position and start
  for (
      xx = -_worldView->tileWidth() *2;
      xx - _worldView->tileWidth() < _window->width;
      xx += dx, anchor = anchor +vx
      ) 
  {
    //LOG_DEBUG("\n\n")
    for (
        pos = anchor, yy = -_worldView->tileHeight() *2; 
        yy - _worldView->tileHeight() < _window->height ;
        yy += dy, pos = pos +vy
        )
    {
      // Render tile pos at (x, y+offx[!!flip])
      FlatHexPosition off(pos);
      //LOG_DEBUG("%s\n", pos.toString().c_str());
      off.tile().convert(FlatHexPosition::OddQOffset);
      //LOG_DEBUG("%s\n", off.toString().c_str());
      if (
          0 <= off._x && 0 <= off._y 
          && off._x < _world->width() 
          && off._y < _world->height()) 
      {
        _worldView->toPixel(off, &x, &y);
        //LOG_DEBUG("%d,%d -> %d,%d\n", x, y, rect.x, rect.y);
        if (_tilerdr->renderAt(_camera->getOrientation(), 
            x, y, _window->renderer)) 
        {
          LOG_WRN("%s\n", SDL_GetError());
          OUPS();
        }
        
        auto vec(_world->getContentAt(off));
        if (vec) {
          for (auto peon : *vec) {
            _worldView->toPixel(peon->pos(), &x, &y);
            _peonrdr->renderAt(_camera->getOrientation(), 
                x, y, _window->renderer);
          }
        }
      }
      //LOG_DEBUG("\n")
    }
  }
}