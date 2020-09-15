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
/// \file   SpriteAsset.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 15 septembre 2020, 13:41
///

#include "SpriteAsset.h"
#include "SpriteSheet.h"

/// \brief Create an asset from a loaded SpriteSheet
SpriteAsset::SpriteAsset(std::unique_ptr<SpriteSheet> sheet) : 
  _sheet(std::move(sheet))
{
  
}

/// \brief Load an asset from given file
std::unique_ptr<SpriteAsset> SpriteAsset::loadFromFile(
  const char *path, 
  SDL_Renderer *rdr)
{
  // Load the sprite
  auto sheet(SpriteSheet::loadFromFile(path, 1, 1, rdr));
  if (!sheet) return nullptr;
  // Recut the sheet
  int width(sheet->width() / 6), rows;
  rows = sheet->height() / width;
  if (sheet->recut(rows, 6)) return nullptr;
  // done
  return std::make_unique<SpriteAsset>(std::move(sheet));
}

/// \brief return number of frames in the animation
int SpriteAsset::animationFrames() const {
  return _sheet->rowCount();
}

/// \brief render the sprite at given dest
/// \param dir   : Sprite orientation
/// \param frame : Animation's frame
/// \param rdr   : Targeted renderer
/// \param dest  : drawing target
int SpriteAsset::render(
  unsigned int dir, 
  unsigned int frame, 
  SDL_Renderer *rdr, 
  const SDL_Rect *dest)
{
  return _sheet->renderFrame(frame, dir, rdr, dest);
}