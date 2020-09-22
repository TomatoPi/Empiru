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
/// \date 16 septembre 2020, 11:05
///

#include <cassert>

#include "WorldObject.h"

/// \brief Construct a Tile Sized Object
WorldObject::WorldObject() : 
  _pos(), _size(STile), _radius(1) 
{
  
}
/// \brief Construct a Small Sized Object with given radius
WorldObject::WorldObject(float radius) : 
  _pos(), _size(SSmall), _radius(radius) 
{
  
}
/// \brief Contruct a Hollow Sized Object
WorldObject::WorldObject(void * osef) : 
  _pos(), _size(SHollow), _radius(0)
{
  
}

/// \brief return object's position
const FlatHexPosition & WorldObject::pos() const {
  return _pos;
}
/// \brief set object's position
void WorldObject::pos(const FlatHexPosition & pos) {
  _pos = pos;
}

/// \brief return object's size class
WorldObject::Size WorldObject::sizeClass() const {
  return _size;
}
/// \brief return object's radius or 1 if tile sized
float WorldObject::radius() const {
  return _radius;
}

/// \brief Method that must return true is 'pos' is in object's hitbox
bool WorldObject::collide(const WorldObject & obj) const {
  if (_size == SHollow || obj._size == SHollow)
    return false;
  if (_size == SSmall) {
    if (obj._size == SSmall)
      return smallCollide(*this, obj);
    return stCollide(*this, obj);
  } else {
    if (obj._size == SSmall)
      return stCollide(obj, *this);
    return tileCollide(*this, obj);
  }
}
bool WorldObject::collide(const FlatHexPosition & pos) const {
  if (_size == SHollow) return false;
  if (_size == SSmall) {
    return FlatHexPosition::distance(pos, _pos) < _radius;
  } else {
    return _pos.tile() == pos.tile();
  }
}

/// \brief Collision between two small objects
bool WorldObject::smallCollide(const WorldObject &a, const WorldObject &b) {
  return FlatHexPosition::distance(a._pos, b._pos) < (a._radius + b._radius);
}
/// \brief Collision between two tile objects
bool WorldObject::tileCollide(const WorldObject &a, const WorldObject &b) {
  return a._pos.tile() == b._pos.tile();
}
/// \brief Collision between a small object and a tile object
bool WorldObject::stCollide(const WorldObject &small, const WorldObject &tile) {
  // Easier to understand with a drawing
  return (small._pos + FlatHexPosition(small._pos, tile._pos).toUnit() * small._radius).toTile() == tile._pos.tile();
}