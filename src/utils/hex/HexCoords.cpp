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
/// \file   HexCoords.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 8 septembre 2020, 02:38
///

#include "HexCoords.h"
#include "utils/log.h"
#include "utils/math/Math.h"

#include <cassert>
#include <cmath>

/// \brief Axial (0,0)
FlatHexPosition::FlatHexPosition() : 
  FlatHexPosition(0,0,0,Axial) 
{
  
}
/// \brief System's (0,0)
FlatHexPosition::FlatHexPosition(System type) : 
  FlatHexPosition(0,0,0,type) 
{
  
}
/// \brief System's (x,y)
FlatHexPosition::FlatHexPosition(float x, float y, System type) : 
  FlatHexPosition(x, y, 0, type)
{
  
}
/// \brief Build a position from another
FlatHexPosition::FlatHexPosition(const FlatHexPosition & pos, System type) :
  FlatHexPosition(pos)
{
  convert(this, type);
}
/// \brief Cubic (x,y,z)
FlatHexPosition::FlatHexPosition(float x, float y, float z) : 
  FlatHexPosition(x, y, z, Cubic)
{
  
}
/// \brief Construct a position from Pixel Coordinate
FlatHexPosition::FlatHexPosition(float x, float y, float w, float h, System type) :
  FlatHexPosition(4*x/w, 2*y/h, 0, Grid)
{
  convert(this, type);
}
/// \brief Build vector AB
FlatHexPosition::FlatHexPosition(
    const FlatHexPosition & A, 
    const FlatHexPosition & B) :
  FlatHexPosition(B - A)
{
}
/// \brief Effective constructor
FlatHexPosition::FlatHexPosition(float x, float y, float z, System s) : 
  _x(x), _y(y), _z(z), _type(s)
{
  
}

/// \brief return true if a is at the same position than this
bool FlatHexPosition::operator==(const FlatHexPosition & a) const {
  FlatHexPosition u(*this, Axial), v(a, Axial);
  return u._x == v._x && u._y == v._y;
}
/// \brief return !(a==b)
bool FlatHexPosition::operator!=(const FlatHexPosition & a) const {
  return ! (*this == a);
}

/// \brief scale vector by 'f' factor
/// \return Axial vector
FlatHexPosition FlatHexPosition::operator*(const float & f) const {
  FlatHexPosition res(*this, Axial);
  res._x *= f;
  res._y *= f;
  return res;
}
/// \brief add up two vector
/// \return Axial vector
FlatHexPosition FlatHexPosition::operator+(const FlatHexPosition & v) const {
  FlatHexPosition a(*this, Axial), b(v, Axial), res(Axial);
  res._x = a._x + b._x;
  res._y = a._y + b._y;
  return res;
}
/// \brief substract two vector
/// return this - v as Axial Vector
FlatHexPosition FlatHexPosition::operator-(const FlatHexPosition & v) const {
  FlatHexPosition a(*this, Axial), b(v, Axial), res(Axial);
  res._x = a._x - b._x;
  res._y = a._y - b._y;
  return res;
}
/// \brief get oposite vector
/// \return Axial vector
FlatHexPosition FlatHexPosition::operator-() const {
  FlatHexPosition res(*this, Axial);
  res._x = -res._x;
  res._y = -res._y;
  return res;
}
/// \brief Multiply this by matrix M
/// \return this as Axial Vector
FlatHexPosition FlatHexPosition::operator*(const Matrix22 & M) const {
  FlatHexPosition res(*this, Axial);
  float x = res._x * M._a + res._y * M._b;
  float y = res._x * M._c + res._y * M._d;
  res._x = x;
  res._y = y;
  return res;
}

/// \brief return distance between this and b
float FlatHexPosition::distance(
    const FlatHexPosition & a, 
    const FlatHexPosition & b) 
{
  FlatHexPosition v(a, b);
  v.convert(Axial);
  return std::hypotf(v._x, v._y);
}

/// \brief Convert this position to 'target' System
FlatHexPosition & FlatHexPosition::convert(System target) {
  return convert(this, target);
}
/// \brief Return this position converted to 'target' system
FlatHexPosition FlatHexPosition::convert(System target) const {
  return FlatHexPosition(*this, target);
}
/// \brief Effective implementation of convert function
FlatHexPosition & FlatHexPosition::convert2(
  FlatHexPosition * pos, System target) 
{
  if (target == pos->_type) {
    return *pos;
  }
  // Convert this position to Axial
  float x, y;
  switch (pos->_type) {
  case OddQOffset :
    x = pos->_x;
    y = pos->_y - (pos->_x - ((int)pos->_x & 1)) / 2.;
    break;
  case Axial :
  case Cubic :
    x = pos->_x;
    y = pos->_y;
    break;
  case Grid :
    x = pos->_x / 3.;
    y = pos->_y / 2. - pos->_x / 6.;
    break;
  default:
    assert(0);
  }
  // Convert from Axial to Target
  switch (target) {
  case OddQOffset :
    pos->_x = x;
    pos->_y = y + (x - ((int)(x) & 1)) / 2.;
    pos->_z = 0;
    break;
  case Axial :
    pos->_x = x;
    pos->_y = y;
    pos->_z = 0;
    break;
  case Cubic :
    pos->_x = x;
    pos->_y = y;
    pos->_z = x - y;
    break;
  case Grid :
    pos->_x = 3 * x;
    pos->_y = 2 * y + x;
    pos->_z = 0;
    break;
  default :
    assert(0);
  }
  // This is the end
  pos->_type = target;
  return *pos;
}

FlatHexPosition & FlatHexPosition::convert(
  FlatHexPosition* pos, System target) 
{
  if (target == pos->_type) {
    return *pos;
  }
  // Convert this position to Axial
  switch (pos->_type) {
  case FlatHexPosition::OddQOffset :
    pos->_y = pos->_y - (pos->_x - ((int)pos->_x & 1)) / 2.;
    break;
  case FlatHexPosition::Axial :
  case FlatHexPosition::Cubic :
    break;
  case FlatHexPosition::Grid :
    pos->_y = pos->_y / 2. - pos->_x / 6.;
    pos->_x /= 3.;
    break;
  default:
    assert(0);
  }
  // Convert from Axial to Target
  switch (target) {
  case FlatHexPosition::OddQOffset :
    pos->_y = pos->_y + (pos->_x - ((int)(pos->_x) & 1)) / 2.;
    break;
  case FlatHexPosition::Axial :
    break;
  case FlatHexPosition::Cubic :
    pos->_z = pos->_x - pos->_y;
    break;
  case FlatHexPosition::Grid :
    pos->_y = 2 * pos->_y + pos->_x;
    pos->_x = 3 * pos->_x;
    break;
  default :
    assert(0);
  }
  // This is the end
  pos->_type = target;
  return *pos;
}

/// \brief Round position to it tile's center
FlatHexPosition & FlatHexPosition::tile() {
  return FlatHexPosition::tile(this);
}
/// \brief Return position rounded to tile's center
FlatHexPosition FlatHexPosition::tile() const {
  FlatHexPosition res(*this);
  return FlatHexPosition::tile(&res);
}

/// \brief Effective implementation of tile function
FlatHexPosition & FlatHexPosition::tile(FlatHexPosition *pos) {
  pos->convert(Axial);
  int x(math::fastmrnd(pos->_x)), y(math::fastmrnd(pos->_y));
  float xx = pos->_x - x, yy = pos->_y - y;
  float u = xx + 2*yy, v = 2*xx + yy, w = yy - xx;
  if (w < 0) {
    if (u < -1) {
      y--;
    } else if (v > 1) {
      x++;
    }
  } else {
    if (v < -1) {
      x--;
    } else if (u > 1) {
      y++;
    }
  }
  pos->_x = x, pos->_y = y;
  return *pos;
}
  
/// \brief Normalize to unitatry vector
FlatHexPosition & FlatHexPosition::unit() {
  return unit(this);
}
/// \brief Return as unitary vector
FlatHexPosition FlatHexPosition::unit() const {
  FlatHexPosition res(*this);
  return unit(&res);
}
/// \brief Effective implementation of unit function
FlatHexPosition & FlatHexPosition::unit(FlatHexPosition *pos) {
  pos->convert(Axial);
  float norm(1.0f / std::hypotf(pos->_x, pos->_y));
  pos->_x *= norm, pos->_y *= norm;
  return *pos;
}

/// \brief toString
std::string FlatHexPosition::toString() const {
  return "HexPos[" + systemString(_type) + ":(" 
      + std::to_string(_x) + "," 
      + std::to_string(_y) + ","
      + std::to_string(_z) + ")]";
}
/// \brief Return s as a string
std::string FlatHexPosition::systemString(System s) {
  switch(s) {
  case OddQOffset:
    return "OddQOffset";
  case Axial:
    return "Axial     ";
  case Cubic:
    return "Cubic     ";
  case Grid:
    return "Grid      ";
  default:
    assert(0);
    return "";
  }
}

/// \brief Return vector major orientation between 0 and 5 (incl)
///   with 0 on bottom's verticle and turning counter-clockwise
int FlatHexPosition::orientation() const {
  float u = _x + 2*_y, v = 2*_x + _y, w = _y - _x;
  static int hexans[2][2][2] = {{{0, 11}, {5, 4}}, {{1, 2}, {16, 3}}};
  assert(hexans[w<0][v<0][u<0] < 6);
  return hexans[w<0][v<0][u<0];
}

/// \brief Hashing functor on FlatHexPositions objects
///   Hashing is performed on position rounded to it's tile
///   So two positions on the same tile will have the same hash
std::size_t HCHasher::operator() (const FlatHexPosition &obj) const {
  FlatHexPosition pos = obj.tile().convert(FlatHexPosition::Axial);
  size_t x(pos._x), y(pos._y);
  return x ^ ((y << 16) | (y >> (sizeof(size_t) * 8 - 16)));
}

/// \brief Equality functor on FlatHexPosition objects
///   Equality is tested on position rounded to it's tile
///   So if 'a' and 'b' are on the same tile, return will be true
bool HCEquals::operator() (const FlatHexPosition &a, const FlatHexPosition &b) const {
  return a.tile() == b.tile();
}