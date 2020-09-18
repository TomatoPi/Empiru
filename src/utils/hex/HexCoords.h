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
/// \file   HexCoords.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 8 septembre 2020, 02:38
/// \brief File containing utilities for Hexagonal Grids
///
/// \see https://www.redblobgames.com/grids/hexagons/
///

#ifndef HEXCOORDS_H
#define HEXCOORDS_H

#include <string>
#include <functional>
#include "utils/math/Matrix.h"

/// \brief Represent a position on an Hexagonal Grid with flat disposition
/// \todo Profile conversion and systems usage
struct FlatHexPosition {
  
  /// \enum System List of available coordinate systems
  enum System {
    OddQOffset, ///< Odd-q Offset System
    Axial,      ///< Axial System
    Cubic,      ///< Cubic System
    Grid,       ///< Grid System in (0.75w, 0.5h) basis
  };

  float   _x;     ///< Horizontal or RightDown position
  float   _y;     ///< Vertical Position
  float   _z;     ///< RightUp position in Cubic System
  System  _type;  ///< Position's Coordinate System
  
  /// \brief Axial (0,0)
  FlatHexPosition();
  /// \brief System's (0,0)
  FlatHexPosition(System type);
  /// \brief System's (x,y)
  FlatHexPosition(float x, float y, System type);
  /// \brief Build a position from another
  FlatHexPosition(const FlatHexPosition & pos, System type);
  /// \brief Cubic (x,y,z)
  FlatHexPosition(float x, float y, float z);
  /// \brief Construct a position from Grid Coordinate
  FlatHexPosition(float x, float y, float w, float h, System type);
  /// \brief Build vector AB
  FlatHexPosition(const FlatHexPosition & A, const FlatHexPosition & B);
  
  /// \brief return true if a is at the same position than this
  bool operator==(const FlatHexPosition & a) const;
  /// \brief return !(a==b)
  bool operator!=(const FlatHexPosition & a) const;
  
  /// \brief scale vector by 'f' factor
  /// \return Axial vector
  FlatHexPosition operator*(const float & f) const;
  /// \brief add up two vectors
  /// \return Axial vector
  FlatHexPosition operator+(const FlatHexPosition & v) const;
  /// \brief substract two vectors
  /// \return this - v as Axial Vector
  FlatHexPosition operator-(const FlatHexPosition & v) const;
  /// \brief get oposite vectors
  /// \return Axial vector
  FlatHexPosition operator-() const;
  /// \brief Multiply this by matrix M
  /// \return this as Axial Vector
  FlatHexPosition operator*(const Matrix22 & M) const;
  
  /// \brief Call given function on this tile and each adjacent ones
  ///   this function stops after first tile on which func return true
  ///   or after tested all 7 tiles
  /// System of position passed to callback is the same as curent system
  void mapNeightbours(std::function<bool(const FlatHexPosition &)> func) const;
  
  /// \brief return distance between a and b
  static float distance(
    const FlatHexPosition & a, 
    const FlatHexPosition & b);
  
  /// \brief Convert this position to 'target' System
  FlatHexPosition & convertTo(System target);
  /// \brief Return this position converted to 'target' system
  FlatHexPosition convert(System target) const;
  
  /// \brief Round position to it tile's center
  FlatHexPosition & toTile();
  /// \brief Return position rounded to tile's center
  FlatHexPosition tile() const;
  
  /// \brief Normalize to unitatry vector
  FlatHexPosition & toUnit();
  /// \brief Return as unitary vector
  FlatHexPosition unit() const;
  
  /// \brief toString
  std::string toString() const;
  /// \brief Return s as a string
  static std::string systemString(System s);
  
  /// \brief Return vector major orientation between 0 and 5 (incl)
  ///   with 0 on bottom's verticle and turning counter-clockwise
  int orientation() const;
  
private:
  
  /// \brief Effective constructor
  FlatHexPosition(float x, float y, float z, System s);
  
  /// \brief Effective implementation of tile function
  static FlatHexPosition & tile(FlatHexPosition *pos);
  /// \brief Effective implementation of unit function
  static FlatHexPosition & unit(FlatHexPosition *pos);
  /// \brief Effective implementation of convert function
  static FlatHexPosition & convert(FlatHexPosition * pos, System target);
  /// \brief Effective implementation of convert function
  static FlatHexPosition & convert2(FlatHexPosition * pos, System target);
};

/// \brief Hashing functor on FlatHexPosition objects
///   Hashing is performed on position rounded to it's tile
///   So two positions on the same tile will have the same hash
class HCHasher {
public :
  std::size_t operator() (const FlatHexPosition &obj) const;
};

/// \brief Equality functor on FlatHexPosition objects
///   Equality is tested on position rounded to it's tile
///   So if 'a' and 'b' are on the same tile, return will be true
class HCEquals {
public :
  bool operator() (const FlatHexPosition &a, const FlatHexPosition &b) const;
};

#endif /* HEXCOORDS_H */
