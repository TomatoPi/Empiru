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

SpriteSheet::SpriteSheet(SDL_Texture *t, 
          int w, int h,
          unsigned int rows, 
          unsigned int cols) :
  _sheet(t),
  _w(w),
  _h(h),
  _rows(rows),
  _cols(cols)
{
  assert(t);
  assert(0 < w);
  assert(0 < h);
  assert(0 < rows);
  assert(0 < cols);
}

SpriteSheet::~SpriteSheet() {
  SDL_DestroyTexture(_sheet);
}

std::unique_ptr<SpriteSheet> SpriteSheet::loadFromFile(
    const char *path, 
    unsigned int rows,
    unsigned int cols,
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
  if (nullptr == (rwop = SDL_RWFromFile(path, "rb"))) {
    LOG_WRN("%s : %s\n", path, SDL_GetError());
    return nullptr;
  }
  if (nullptr == (surface = IMG_Load_RW(rwop, 1))) {
    LOG_WRN("%s : %s\n", path, IMG_GetError());
    return nullptr;
  }
  /* Conversion Récupération des infos */
  if (nullptr == (texture = SDL_CreateTextureFromSurface(rdr, surface))) {
    LOG_WRN("%s : %s\n", path, SDL_GetError());
    SDL_FreeSurface(surface);
    return nullptr;
  }
  SDL_FreeSurface(surface);
  auto sprite(std::make_unique<SpriteSheet>(texture, 1, 1, rows, cols));
  if (sprite->recut(rows, cols)) {
    sprite.reset();
    return nullptr;
  }
  /* finitions */
  return sprite;
}

int SpriteSheet::renderFrame(
  unsigned int row,
  unsigned int col,
  SDL_Renderer *rdr,
  const SDL_Rect *dest)
{
  assert(rdr);
  assert(row < _rows);
  assert(col < _cols);
  SDL_Rect rect;
  rect.w = _w, rect.h = _h, rect.x = col * _w, rect.y = row * _h;
  return SDL_RenderCopy(rdr, _sheet, &rect, dest);
}

int SpriteSheet::width() const {
  return _w;
}
int SpriteSheet::height() const {
  return _h;
}

unsigned int SpriteSheet::colCount() const {
  return _cols;
}
unsigned int SpriteSheet::rowCount() const {
  return _rows;
}

int SpriteSheet::recut(unsigned int rows, unsigned int cols) {
  int width, height;
  if (0 != SDL_QueryTexture(_sheet, nullptr, nullptr, &width, &height)) {
    LOG_WRN("%s\n", SDL_GetError());
    return -1;
  }
  if ((width % cols) != 0 || (height % rows) != 0) {
    LOG_WRN("Ill formed Sprite Sheet ... inequals sprites\n");
  }
  width /= rows, height /= cols;
  if (width != height) {
    LOG_WRN("Non square sprites are not recomended (%dx%d)\n", 
        width, height);
  }
  _w = width, _h = height, _rows = rows, _cols = cols;
  return 0;
}