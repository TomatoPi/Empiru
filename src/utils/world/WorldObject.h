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
/// \file   WorldObject.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 16 septembre 2020, 10:51
///

#ifndef WORLD_WORLDOBJECT_H
#define WORLD_WORLDOBJECT_H

#include "utils/hex/Axial.h"
#include <cassert>

/// \brief Base polymorphic object for things on the map
/// Each object is caracterized by a position and a pseudo hitbox
/// Hitbox is the space on floor occupied by the object
class WorldObject {
public:
  
  /// \brief Specify object's size on the map
  enum Size {
    SSmall,  ///< Objects that can coexist on the same tile with circular hitbox
    STile,   ///< Objects that occupy the whole tile
    SHollow, ///< Utility objects that don't occupy space
  };
  
  typedef hex::Axial Position;
  
private:
  
  Position _pos;     ///< Object's position
  float    _radius;  ///< Hitbox radius for small objects
  Size     _size;    ///< Object's size
  
public:
  
  /// \brief Construct a Tile Sized Object
  WorldObject(Size size, float radius=0.5f, Position pos=Position()) noexcept :
    _pos(pos),
    _radius(radius),
    _size(size)
  {
  }
  /// \brief Copy constructor
  WorldObject(const WorldObject &) noexcept = default;
  /// \brief Copy assignement
  WorldObject & operator= (const WorldObject &) noexcept = default;
  /// \brief Destructor
  virtual ~WorldObject() noexcept = default;
  
  /// \brief return object's position
  const Position & pos() const noexcept {
    return _pos;
  } 
  /// \brief set object's position
  void pos(const Position & pos) noexcept {
    _pos = pos;
  }
  
  /// \brief return object's size class
  Size sizeClass() const noexcept {
    return _size;
  }
  /// \brief return object's radius or 1 if tile sized
  float radius() const noexcept {
    return _radius;
  }
  
  /// \brief Method that must return true obj collides this object
  virtual bool collide(const WorldObject & obj) const noexcept {
    if (_size == SHollow || obj._size == SHollow)
      return false;
    if (_size == SSmall) {
      if (obj._size == SSmall)
        return smallCollide(*this, obj);
      return stCollide(*this, obj);
    }
    if (_size == STile) {
      if (obj._size == SSmall)
        return stCollide(obj, *this);
      return tileCollide(*this, obj);
    }
    assert(0);
    return false;
  }
  /// \brief Method that return true if pos is in this object
  virtual bool collide(const Position & pos) const noexcept {
    if (_size == SHollow) return false;
    if (_size == SSmall) {
      return Position::distance(pos, _pos) < _radius;
    }
    if (_size == STile) {
      return _pos.tile() == pos.tile();
    }
    assert(0);
    return false;
  }
  
public:
  
  /// \brief Collision between two small objects
  static bool smallCollide(const WorldObject &a, const WorldObject &b) 
    noexcept 
  {
    return Position::distance(a._pos, b._pos) < (a._radius + b._radius);
  }
  /// \brief Collision between two tile objects
  static bool tileCollide(const WorldObject &a, const WorldObject &b)
    noexcept
  {
    return a._pos.tile() == b._pos.tile();
  }
  /// \brief Collision between a small object and a tile object
  static bool stCollide(const WorldObject &small, const WorldObject &tile)
    noexcept
  {
    // Easier to understand with a drawing
    return Position(
        small._pos + (small._pos - tile._pos).toUnit() 
          * small._radius).tile() == tile._pos.tile();
  }
};

#endif /* WORLD_WORLDOBJECT_H */

