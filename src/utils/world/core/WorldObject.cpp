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
/// \date 8 octobre 2020, 22:41
///

#include <cassert>
#include "WorldObject.h"

WorldObject::WorldObject(Size size, float radius, Position pos) noexcept :
  _pos(pos),
  _radius(radius),
  _size(size)
{
}

/// \brief Method that must return true obj collides this object
bool WorldObject::collide(const WorldObject & obj) const noexcept {
  if (_size == Size::Hollow || obj._size == Size::Hollow)
    return false;
  if (_size == Size::Small) {
    if (obj._size == Size::Small)
      return smallCollide(*this, obj);
    return stCollide(*this, obj);
  }
  if (_size == Size::Tile) {
    if (obj._size == Size::Small)
      return stCollide(obj, *this);
    return tileCollide(*this, obj);
  }
  assert(0);
  return false;
}

/// \brief Method that return true if pos is in this object
bool WorldObject::collide(const Position & pos) const noexcept {
  if (_size == Size::Hollow) return false;
  if (_size == Size::Small) {
    return Position::distance(pos, _pos) < _radius;
  }
  if (_size == Size::Tile) {
    return _pos.tile() == pos.tile();
  }
  assert(0);
  return false;
}