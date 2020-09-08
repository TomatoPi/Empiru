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
/// \file   Sprite.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 8 septembre 2020, 04:28
///

#include <cassert>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rwops.h>

#include "Sprite.h"

#include "utils/log.h"

Sprite::Sprite(SDL_Texture *t, int w, int h) :
  _sprite(t),
  _w(w),
  _h(h)
{
  assert(t);
  assert(0 < w);
  assert(0 < h);
}

Sprite::~Sprite() {
  SDL_DestroyTexture(_sprite);
}

Sprite * Sprite::loadFromFile(const char *path, SDL_Renderer *rdr) {
  SDL_Surface *surface;
  SDL_Texture *texture;
  SDL_RWops   *rwop;
  int width, height;
  /* assertions */
  assert(path);
  assert(rdr);
  /* Chargement du fichier */
  if (NULL == (rwop = SDL_RWFromFile(path, "rb"))) {
    LOG_WRN("%s\n", SDL_GetError());
    return NULL;
  }
  if (NULL == (surface = IMG_Load_RW(rwop, 1))) {
    LOG_WRN("%s\n", IMG_GetError());
    return NULL;
  }
  /* Conversion Récupération des infos */
  if (NULL == (texture = SDL_CreateTextureFromSurface(rdr, surface))) {
    LOG_WRN("%s\n", SDL_GetError());
    SDL_FreeSurface(surface);
    return NULL;
  }
  SDL_FreeSurface(surface);
  if (0 != SDL_QueryTexture(texture, NULL, NULL, &width, &height)) {
    LOG_WRN("%s\n", SDL_GetError());
    SDL_DestroyTexture(texture);
    return NULL;
  }
  /* finitions */
  return new Sprite(texture, width, height);
}

int Sprite::renderFrame(
  SDL_Renderer *rdr,
  const SDL_Rect *dest)
{
  assert(rdr);
  return SDL_RenderCopy(rdr, _sprite, NULL, dest);
}

int Sprite::width() const {
  return _w;
}
int Sprite::height() const {
  return _h;
}