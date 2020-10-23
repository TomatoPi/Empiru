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
/// \file   Builder.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 24 octobre 2020, 00:10
///

#include "Builder.h"

namespace decorators {
  void WorldObjectBuilder::operator() (core::Pointer& ptr) const noexcept {
    this->core::Builder::operator() (ptr);
    WorldObject& obj(static_cast<WorldObject&>(*ptr));
    obj._entity = _entity;
    obj._pos = _pos;
    obj._radius = _radius;
    obj._size = _size;
    obj._orientation = _orientation;
  }
}