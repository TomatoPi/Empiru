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
  HexCamera camera(sprite->width(), HexCamera::HEXAGON_HEIGHT);
  
  LOG_DEBUG("Window : %d,%d\nSprite : %d,%d\nCamera : %d,%d\n", 
      window->width, window->height,
      sprite->width(), sprite->height(),
      camera.tileWidth(), camera.tileHeight());
  
  camera.target(AxialPosition(0,0));

  window->clear();
  SDL_Rect rect;
  rect.w = sprite->width();
  rect.h = sprite->height();
  rect.x = 0;
  rect.y = 0;
  
  OQOffsetPosition tmp, anchor;
  GridPosition pos;
  
  camera.upLeftCorner(window->width, window->height, &anchor);
  LOG_DEBUG("Anchor : %f,%f\n", anchor._row, anchor._col);
  
  tmp._col = anchor._col;
  while(rect.x < window->width) {
    tmp._row = anchor._row;
    rect.y = 0;
    while(rect.y < window->height) {
      convertPosition(tmp, &pos);
      camera.toPixel(pos, &(rect.x), &(rect.y));
      //LOG_DEBUG("OFF : (%f,%f)\nPOS : (%f,%f)\nPIX : (%d,%d)\n",
      //    tmp._col, tmp._row, pos._w, pos._h, rect.x, rect.y);
      rect.x += window->width/2;
      rect.y += camera.tileHeight() - rect.h + window->height/2;
      if (0 <= tmp._col && 0 <= tmp._row)
        if (sprite->renderFrame(window->renderer, &rect)) {
          LOG_WRN("%s\n", SDL_GetError());
          OUPS();
        }
      tmp._row++;
    }
    tmp._col++;
    convertPosition(tmp, &pos);
    camera.toPixel(pos, &(rect.x), &(rect.y));
  }
  
  window->update();
  
  while(!window->quitRequest());
  
  return 0;
}

