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
/// \brief Provide basic object to load and draw sprites using sprite sheet
///

#include <cassert>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rwops.h>
#include <SDL2/SDL_surface.h>
#include <stdexcept>

#include "SpriteSheet.h"

#include "utils/log.h"

/// \brief Constructor
SpriteSheet::SpriteSheet(SDL_Texture *t, 
          int w, int h,
          unsigned int rows, 
          unsigned int cols) 
noexcept :
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

/// \brief Destructor
SpriteSheet::~SpriteSheet() noexcept {
  SDL_DestroyTexture(_sheet);
}

/// \brief Loads a sprite from an image file
///
/// \param path : file's path
/// \param rows : number of frames by row
/// \param cols : number of frames by column
/// \param rdr  : SDL_Renderer associated with targeted viewport
///
/// \return NULL on failure
std::unique_ptr<SpriteSheet> SpriteSheet::loadFromFile(
    const char *path, 
    unsigned int rows,
    unsigned int cols,
    SDL_Renderer *rdr) 
{
  /* assertions */
  assert(path);
  assert(rdr);
  /* tmp objects */
  SDL_Surface *surface(nullptr);
  SDL_Texture *texture(nullptr);
  try {
    /* load the file */
    if (nullptr == (surface = IMG_Load(path))) {
      throw std::runtime_error(IMG_GetError());
    }
    /* transform image to texture */
    if (nullptr == (texture = SDL_CreateTextureFromSurface(rdr, surface))) {
      throw std::runtime_error(SDL_GetError());
    }
    SDL_FreeSurface(surface);
    /* create the sheet and cut it according to wanted dimensions */
    auto sprite(std::make_unique<SpriteSheet>(texture, 1, 1, rows, cols));
    sprite->recut(rows, cols);
    return sprite;
  } catch (const std::exception & e) {
    LOG_WRN("%s : %s\n", path, e.what());
    throw;
  }
}

/// \brief Render the sprite in given SDL_Rect
/// 
/// \param row  : sprite's row on the sheet
/// \param col  : sprite's column on the sheet
/// \param rdr  : the thing that draw things
/// \param dest : the destination blit rectangle
///
/// \throw runtime_error on failure
void SpriteSheet::renderFrame(
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
  if (SDL_RenderCopy(rdr, _sheet, &rect, dest)) {
    throw std::runtime_error(SDL_GetError());
  }
}

/// \brief Change color of the sprite
/// \throw runtime_error on failure
void SpriteSheet::setColorMod(const SDL_Color & c) {
  if (SDL_SetTextureColorMod(_sheet, c.r, c.g, c.b)) {
    throw std::runtime_error(SDL_GetError());
  }
}

/// \brief return sprite's width
int SpriteSheet::width() const noexcept {
  return _w;
}
/// \brief return sprite's height
int SpriteSheet::height() const noexcept {
  return _h;
}

/// \brief return number of frames by row on the sheet
unsigned int SpriteSheet::colCount() const noexcept {
  return _cols;
}
/// \brief return number of frames by column on the sheet
unsigned int SpriteSheet::rowCount() const noexcept {
  return _rows;
}

/// \brief change number of frames by rows and by columns on the sheet
///   if resulting sheet is ill formed (width%cols != 0 or height%rows != 0)
///   accessing last (smaller) sprites may cause undefined behaviour
/// \throw runtime_error on failure
void SpriteSheet::recut(unsigned int rows, unsigned int cols) {
  int width, height;
  if (0 != SDL_QueryTexture(_sheet, nullptr, nullptr, &width, &height)) {
    throw std::runtime_error(SDL_GetError());
  }
  if ((width % cols) != 0 || (height % rows) != 0) {
    LOG_WRN("Ill formed Sprite Sheet ... inequals sprites\n");
  }
  width /= cols, height /= rows;
  _w = width, _h = height, _rows = rows, _cols = cols;
}