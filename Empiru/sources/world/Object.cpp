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
/// \file   Object.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 27 oct. 2020 01:55:39
///
#include "Object.h"

namespace world {

Object::Object(const Pointer &ptr) noexcept :
    _this(ptr), _entity(), _pos(), _radius(), _orientation(), _size() {
}

void Object::build(game::EUID entity, Size s, const Position &pos, float r,
    int o) noexcept {
  _size = s;
  _pos = pos;
  _entity = entity;
  _radius = r;
  _orientation = o;
}

bool Object::collide(const Object &obj, const Position &pos) const noexcept {
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
}

