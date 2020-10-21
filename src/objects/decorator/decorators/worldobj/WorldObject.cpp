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
/// \date 21 octobre 2020, 12:08
///

#include "WorldObject.h"

void WorldObject::Builder::operator() (core::Pointer& ptr) const noexcept {
  this->Decorator::Builder::operator() (ptr);
  WorldObject& obj(static_cast<WorldObject&>(*ptr));
  obj._pos = _pos;
  obj._radius = _radius;
  obj._size = _size;
  obj._orientation = _orientation;
}

bool 
WorldObject::collide(const WorldObject& obj, const world::Position& pos) 
const noexcept {
  if (_size == Size::Hollow || obj._size == Size::Hollow)
    return false;
  if (_size == Size::Small) {
    if (obj._size == Size::Small)
      return smallCollide(*this, _pos, obj, pos);
    return stCollide(*this, _pos, obj, pos);
  }
  if (_size == Size::Tile) {
    if (obj._size == Size::Small)
      return stCollide(obj, pos, *this, _pos);
    return tileCollide(_pos, pos);
  }
  assert(0);
  return false;
}