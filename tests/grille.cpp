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

/* 
 * File:   grille.cpp
 * Author: DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 *
 * Created on 11 septembre 2020, 04:23
 */

#include <stdlib.h>
#include <iostream>
#include <cmath>

#include "utils/hex/HexViewport.h"
#include "SDL2/SDL.h"

#include "utils/log.h"

#define WIDTH   (1920/2)
#define HEIGHT  (1080/2)


int rr(float a) {
  return round(a) + ((a < 0) && (fabs(a - round(a)) >= 0.5));
}

int main(int argc, char** argv) {
  
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    LOG_ERROR("Failed Init SDL : %s\n", SDL_GetError());
    return 0;
  }
  SDL_Window *window = SDL_CreateWindow("Foobar2221", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    LOG_ERROR("Failed Create Window : %s\n", SDL_GetError());
    return 0;
  }
  
  SDL_Surface *screen = SDL_GetWindowSurface(window);
  if (!screen) {
    LOG_ERROR("Failed create surface : %s\n", SDL_GetError());
    return 0;
  }
  
  HexViewport camera(
    HexViewport::HEXAGON_WIDTH, HexViewport::HEXAGON_HEIGHT,
    WIDTH, HEIGHT);
  
  SDL_Rect rect;
  rect.w = rect.h = 1;
  
  LOG_INFO("Begin draw ...\n");
  
  for (rect.x = 0; rect.x < WIDTH; ++rect.x) {
    for (rect.y = 0; rect.y < HEIGHT; ++rect.y) {
      FlatHexPosition pos;
      camera.fromPixel(rect.x, rect.y, &pos);
      pos.tile();
      int r = ((int)pos._x * 10) % 256;
      int g = (((int)pos._y + 5) * 17) % 256;
      int b = (((int)pos._x ^ ((int)pos._y << 3)) * 30) % 256;
      if (SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, r,g,b))) {
        LOG_ERROR("Failed fill surface : %s\n", SDL_GetError());
        return 0;
      }
    }
  }
  if (SDL_UpdateWindowSurface(window)) {
    LOG_ERROR("Failed update window : %s\n", SDL_GetError());
    return 0;
  }
  LOG_INFO("Done\n");

  SDL_Event e;
  while (SDL_WaitEvent(&e)) {
    if (e.type == SDL_QUIT) {
      break;
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
      FlatHexPosition pos, tile;
      HCHasher hash;
      camera.fromPixel(e.button.x, e.button.y, &pos);
      pos.convert(FlatHexPosition::Axial);
      tile = pos;
      tile.tile();
      int x(rr(pos._x)), y(rr(pos._y));
      float xx = pos._x - x, yy = pos._y - y;
      float u = xx + 2*yy, v = 2*xx + yy, w = yy - xx;
      LOG_INFO("Clic : (%d,%d) -> %s\n", e.button.x, e.button.y, pos.toString().c_str());
      LOG_INFO("%d,%f  %d,%f  %f %f %f\n", x, xx, y, yy, u, v, w);
      LOG_INFO("Round : %s\n", tile.toString().c_str());
      LOG_INFO("Hash  : %lu\n", hash(pos));
      LOG_INFO("\n");
    }
  }
  
  return (EXIT_SUCCESS);
}

