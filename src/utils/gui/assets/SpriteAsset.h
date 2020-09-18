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
///

#ifndef SPRITEASSET_H
#define SPRITEASSET_H

#include <memory>
#include "utils/gui/assets/SpriteSheet.h"

class SpriteAsset {
public:
  /// \brief Load an asset from given file
  static std::unique_ptr<SpriteSheet> loadFromFile(
    const char *path, 
    SDL_Renderer *rdr);
};

#endif /* SPRITEASSET_H */