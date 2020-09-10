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

/// \brief Represent a position on an Hexagonal Grid with flat disposition
struct FlatHexPosition {

  float _x; ///< Horizontal or RightDown position
  float _y; ///< Vertical Position
  float _z; ///< RightUp position in Cubic System
  
  enum System {
    OddQOffset, ///< Odd-q Offset System
    Axial,      ///< Axial System
    Cubic,      ///< Cubic System
    Grid,       ///< Grid System in (0.75w, 0.5h) basis
  } _type;  ///< Position's Coordinate System
  
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
  
  /// \brief return true if a is at the same position than this
  bool operator==(const FlatHexPosition & a) const;
  
  /// \brief scale vector by 'f' factor
  /// \return Axial vector
  FlatHexPosition operator*(const float & f) const;
  /// \brief add up two vectors
  /// \return Axial vector
  FlatHexPosition operator+(const FlatHexPosition & v) const;
  /// \brief substract two vectors
  /// return this - v as Axial Vector
  FlatHexPosition operator-(const FlatHexPosition & v) const;
  /// \brief get oposite vectors
  /// \return Axial vector
  FlatHexPosition operator-() const;
  
  /// \brief Convert this position to 'target' System
  FlatHexPosition & convert(System target);
  /// \brief Convert this position to 'target' System and store result in 'pos'
  void convert(System target, FlatHexPosition * pos) const;
  
  /// \brief Round position to it tile's center
  FlatHexPosition & tile();
  
  /// \brief toString
  std::string toString() const;
  static std::string systemString(System s);
  
  ///\brief Matrice factor
  void multiply(float a, float b, float c, float d);
};

#endif /* HEXCOORDS_H */
