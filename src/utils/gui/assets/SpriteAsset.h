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
/// \file   SpriteAsset.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 15 septembre 2020, 13:41
/// \brief Utility file for loading and auto cut of sprite sheets
/// \todo Maybe not useful, might be removed and replaced by a function
///   to load sheet by specifying sprite dimension
///

#ifndef SPRITEASSET_H
#define SPRITEASSET_H

#include <memory>
#include "utils/gui/assets/SpriteSheet.h"

/// \brief Must be removed
class SpriteAsset {
public:
  /// \brief Load a sheet from given file and auto cut it in 6 colums
  ///   and squared sprites
  static std::unique_ptr<SpriteSheet> loadFromFile(
    const char *path, 
    SDL_Renderer *rdr);
};

#endif /* SPRITEASSET_H */
