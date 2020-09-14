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
/// \file   SpriteSheet.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 8 septembre 2020, 04:28
///

#include <cassert>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rwops.h>

#include "SpriteSheet.h"

#include "utils/log.h"

SpriteSheet::SpriteSheet(SDL_Texture *t, int w, int h, unsigned int count) :
  _sheet(t),
  _w(w),
  _h(h),
  _framesCount(count)
{
  assert(t);
  assert(0 < w);
  assert(0 < h);
  assert(0 < count);
}

SpriteSheet::~SpriteSheet() {
  SDL_DestroyTexture(_sheet);
}

SpriteSheet * SpriteSheet::loadFromFile(
    const char *path, 
    unsigned int framesCount,
    SDL_Renderer *rdr) 
{
  SDL_Surface *surface;
  SDL_Texture *texture;
  SDL_RWops   *rwop;
  int width, height;
  /* assertions */
  assert(path);
  assert(rdr);
  /* Chargement du fichier */
  if (NULL == (rwop = SDL_RWFromFile(path, "rb"))) {
    LOG_WRN("%s : %s\n", path, SDL_GetError());
    return NULL;
  }
  if (NULL == (surface = IMG_Load_RW(rwop, 1))) {
    LOG_WRN("%s : %s\n", path, IMG_GetError());
    return NULL;
  }
  /* Conversion Récupération des infos */
  if (NULL == (texture = SDL_CreateTextureFromSurface(rdr, surface))) {
    LOG_WRN("%s : %s\n", path, SDL_GetError());
    SDL_FreeSurface(surface);
    return NULL;
  }
  SDL_FreeSurface(surface);
  if (0 != SDL_QueryTexture(texture, NULL, NULL, &width, &height)) {
    LOG_WRN("%s : %s\n", path, SDL_GetError());
    SDL_DestroyTexture(texture);
    return NULL;
  }
  if ((width % framesCount) != 0) {
    LOG_WRN("%s, Ill formed Sprite Sheet ... %d %% %d not zero\n", 
        path, width, framesCount);
  }
  /* finitions */
  return new SpriteSheet(texture, width, height, framesCount);
}

int SpriteSheet::renderFrame(
  unsigned int frame,
  SDL_Renderer *rdr,
  const SDL_Rect *dest)
{
  assert(rdr);
  assert(frame < _framesCount);
  SDL_Rect rect;
  rect.w = _w, rect.h = _h, rect.x = frame * _w, rect.y = 0;
  return SDL_RenderCopy(rdr, _sheet, &rect, dest);
}

int SpriteSheet::width() const {
  return _w;
}
int SpriteSheet::height() const {
  return _h;
}

unsigned int SpriteSheet::framesCount() const {
  return _framesCount;
}