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
/// \file   main.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 6 septembre 2020, 17:18
///

#include <cstdlib>

#include "gui/utils/Sprite.h"
#include "utils/hex/HexCamera.h"
#include "gui/utils/Window.h"

#include "utils/log.h"

using namespace std;

int main(int argc, char** argv) {

  Window *window = Window::createWindow(1920/2, 1080/2);
  Sprite *sprite = Sprite::loadFromFile("medias/sol.png", window->renderer);
  HexCamera camera(
    HexCamera::HEXAGON_WIDTH, HexCamera::HEXAGON_HEIGHT,
    window->width, window->height);
  
  LOG_DEBUG("Window : %d,%d\nSprite : %d,%d\nCamera : %d,%d\n", 
      window->width, window->height,
      sprite->width(), sprite->height(),
      camera.tileWidth(), camera.tileHeight());
  
  camera.target(FlatHexPosition(0,0,FlatHexPosition::Axial));

  window->clear();
  SDL_Rect rect;
  rect.w = sprite->width();
  rect.h = sprite->height();
  rect.x = 0;
  rect.y = 0;
  
  FlatHexPosition anchor, pos, off, vx, vy;
  
  camera.upLeftCorner(&anchor);
  camera.viewPortAxis(&vx, &vy);
  LOG_DEBUG("Anchor : %s\nVx : %s\n Vy : %s\n", 
      anchor.toString().c_str(),
      vx.toString().c_str(),
      vy.toString().c_str());
  
  while((rect.y - rect.h) < window->height) {
    pos = anchor;
    rect.x = 0;
    while(rect.x < window->width) {
      camera.tileCenter(pos, &(rect.x), &(rect.y));
      pos.convert(FlatHexPosition::OddQOffset, &off);
      LOG_DEBUG("Anchor : %s\nPOS : %s\nOFF : %s\nRECT : %d,%d\n",
          anchor.toString().c_str(),
          pos.toString().c_str(),
          off.toString().c_str(),
          rect.x, rect.y);
      if (0 <= off._x && 0 <= off._y) {
        rect.y += 0.5 * camera.tileHeight() - rect.h;
        rect.x -= camera.tileWidth() * 0.5;
        if (sprite->renderFrame(window->renderer, &rect)) {
          LOG_WRN("%s\n", SDL_GetError());
          OUPS();
        }
      }
      pos = pos + vx;
    }
    LOG_DEBUG("=========================\n");
    anchor = anchor + vy;
    camera.tileCenter(anchor, &(rect.x), &(rect.y));
  }
  
  window->update();
  
  while(!window->quitRequest());
  
  return 0;
}

