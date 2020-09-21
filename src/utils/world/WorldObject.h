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

#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include "utils/hex/HexCoords.h"

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
  
private:
  
  FlatHexPosition _pos;     ///< Object's position
  Size            _size;    ///< Object's size
  float           _radius;  ///< Hitbox radius for small objects
  
public:
  
  /// \brief Construct a Tile Sized Object
  WorldObject(const FlatHexPosition & pos);
  /// \brief Construct a Small Sized Object with given radius
  WorldObject(const FlatHexPosition & pos, float radius);
  /// \brief Contruct a Hollow Sized Object
  WorldObject(const FlatHexPosition & pos, void * osef);
  /// \brief Destructor
  virtual ~WorldObject() = default;
  
  /// \brief return object's position
  const FlatHexPosition & pos() const;
  /// \brief set object's position
  void pos(const FlatHexPosition & pos);
  
  /// \brief return object's size class
  Size size() const;
  /// \brief return object's radius or 1 if tile sized
  float radius() const;
  
  /// \brief Method that must return true obj collides this object
  virtual bool collide(const WorldObject & obj) const;
  /// \brief Method that return true if pos is in this object
  virtual bool collide(const FlatHexPosition & pos) const;
  
public:
  
  /// \brief Collision between two small objects
  static bool smallCollide(const WorldObject &a, const WorldObject &b);
  /// \brief Collision between two tile objects
  static bool tileCollide(const WorldObject &a, const WorldObject &b);
  /// \brief Collision between a small object and a tile object
  static bool stCollide(const WorldObject &small, const WorldObject &tile);
};

#endif /* WORLDOBJECT_H */

