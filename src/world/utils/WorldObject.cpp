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
/// \file   WorldObject.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 10 septembre 2020, 13:49
///

#include "WorldObject.h"

const FlatHexPosition & WorldObject::pos() const {
  return _pos;
}

std::size_t WOTileHasher::operator() (const WorldObject & obj) const {
  // renvoyer un hash des coordonées
  return 0;
}

bool WOTileEquals::operator() (const WorldObject & a, const WorldObject & b) const {
  // return true si sur la meme tuile
  return false;
}