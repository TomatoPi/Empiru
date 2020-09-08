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

/*
 * 
 */
int main(int argc, char** argv) {

  Window *window = Window::createWindow(1920/2, 1080/2);
  Sprite *sprite = Sprite::loadFromFile("medias/sol.png", window->renderer);
  HexCamera camera(sprite->width(), HexCamera::vfactor);
  
  LOG_DEBUG("Window : %d,%d\nSprite : %d,%d\nCamera : %f,%f\n", 
      window->width, window->height,
      sprite->width(), sprite->height(),
      camera.tileWidth(), camera.tileHeight());

  window->clear();
  SDL_Rect rect;
  rect.w = sprite->width();
  rect.h = sprite->height();
  rect.x = 0;
  rect.y = 0;
  
  OQOffsetPosition off;
  GridPosition pos;
  
  while(rect.x < window->width) {
    off._lig = 0;
    rect.y = 0;
    while(rect.y < window->height) {
      convertPosition(off, &pos);
      camera.toPixel(pos, &(rect.x), &(rect.y));
      LOG_DEBUG("OFF : (%d,%d)\nPOS : (%f,%f)\nPIX : (%d,%d)\n",
          off._col, off._lig, pos._w, pos._h, rect.x, rect.y);
      if (sprite->renderFrame(window->renderer, &rect)) {
        LOG_WRN("%s\n", SDL_GetError());
        OUPS();
      }
      off._lig++;
    }
    off._col++;
    convertPosition(off, &pos);
    camera.toPixel(pos, &(rect.x), &(rect.y));
  }
  
  window->update();
  
  while(1);
  
  return 0;
}

