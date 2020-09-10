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

#include "WorldRenderer.h"
#include "utils/log.h"

WorldRenderer::WorldRenderer(Window *w, HexCamera *c, Sprite *t) : 
  _window(w),
  _camera(c),
  _tileSprite(t)
{
  assert(w);
  assert(c);
}

void WorldRenderer::render() {
  FlatHexPosition anchor, pos, vx, vy;
  // Compute anchor position and drawsteps
  _camera->upLeftCorner(&anchor);
  _camera->viewPortAxis(&vx, &vy);
  // Move one tile away to always draw left and up tiles
  anchor = anchor - vx -vy;
  // Compute render situation
  int x, y, xx,
      dx(_camera->tileWidth() * 0.75), 
      dy(_camera->tileHeight());
  // -----------------------------------------
  /// \todo remove this
  SDL_Rect rect;
  rect.w = _tileSprite->width();
  rect.h = _tileSprite->height();
  // -----------------------------------------
  // Get initial position and start
  _camera->tileCenter(anchor, &xx, &y);
  for (
      ; 
      y - _camera->tileHeight() < _window->height ;
      y += dy, anchor = anchor +vy
      ) 
  {
    for (
        pos = anchor, x = xx;
        x - _camera->tileWidth()*2.5 < _window->height;
        x += dx, pos = pos +vx
        )
    {
      // Render tile pos at (x, y+offx[!!flip])
      FlatHexPosition off(pos);
      off.tile().convert(FlatHexPosition::OddQOffset);
      //LOG_DEBUG("%s\n", off.toString().c_str());
      if (0 <= off._x && 0 <= off._y && off._x < 8 && off._y < 8) {
        _camera->tileCenter(off, &x, &y);
        rect.x = x - rect.w/2;
        rect.y = y + _camera->tileHeight()/2 - rect.h;
        //LOG_DEBUG("%d,%d -> %d,%d\n", x, y, rect.x, rect.y);
        if (_tileSprite->renderFrame(_window->renderer, &rect)) {
          LOG_WRN("%s\n", SDL_GetError());
          OUPS();
        }
      }
    }
  }
}