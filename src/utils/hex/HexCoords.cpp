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

#include <cassert>
#include <cmath>


/// \brief Axial (0,0)
FlatHexPosition::FlatHexPosition() : 
  FlatHexPosition(0,0,Axial) 
{
  
}
/// \brief System's (0,0)
FlatHexPosition::FlatHexPosition(System type) : 
  FlatHexPosition(0,0,type) 
{
  
}
/// \brief System's (x,y)
FlatHexPosition::FlatHexPosition(float x, float y, System type) : 
  _x(x), _y(y), _z(0), _type(type)
{
  
}
/// \brief Build a position from another
FlatHexPosition::FlatHexPosition(const FlatHexPosition & pos, System type) : FlatHexPosition(pos)
{
  convert(type);
}
/// \brief Cubic (x,y,z)
FlatHexPosition::FlatHexPosition(float x, float y, float z) : 
  _x(x), _y(y), _z(z), _type(Cubic)
{
  
}
/// \brief Construct a position from Pixel Coordinate
FlatHexPosition::FlatHexPosition(float x, float y, float w, float h, System type) :
  _x(4*x/w),
  _y(2*y/h),
  _z(0),
  _type(Grid)
{
  this->convert(type);
}

/// \brief return true if a is at the same position than this
bool FlatHexPosition::operator==(const FlatHexPosition & a) const {
  FlatHexPosition u, v;
  convert(Axial, &u);
  convert(Axial, &v);
  return u._x == v._x && u._y == v._y;
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

/// \brief Convert this position to 'target' System
FlatHexPosition & FlatHexPosition::convert(System target) {
  convert(target, this);
  return *this;
}
/// \brief Convert this position to 'target' System and store result in 'pos'
void FlatHexPosition::convert(System target, FlatHexPosition * pos) const {
  if (target == _type) {
    pos->_type = target;
    pos->_x = _x;
    pos->_y = _y;
    pos->_z = _z;
    return;
  }
  /// Convert this position to Axial
  float x, y;
  switch (_type) {
  case OddQOffset :
    x = _x;
    y = _y - (_x - ((int)_x & 1)) / 2.;
    break;
  case Axial :
  case Cubic :
    x = _x;
    y = _y;
    break;
  case Grid :
    x = _x / 3.;
    y = _y / 2. - _x / 6.;
    break;
  default:
    assert(0);
  }
  /// Convert from Axial to Target
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
  /// This is the end
  pos->_type = target;
}
FlatHexPosition & FlatHexPosition::tile() {
  this->convert(Cubic);
  int x(round(_x + 0.0001)), y(round(_y + 0.0001)), z(round(_z + 0.0001));
  int xx(abs(x-_x)), yy(abs(y-_y)), zz(abs(z-_z));
  if (xx > yy && xx > zz) {
    x = -y-z;
  } else if (yy > zz) {
    y = -x-z;
  } else {
    z = -x-y;
  }
  _x = x, _y = y, _z = z;
  return *this;
}

FlatHexPosition FlatHexPosition::tile() const{
  FlatHexPosition pos(*this,Cubic);
  int x(round(_x + 0.0001)), y(round(_y + 0.0001)), z(round(_z + 0.0001));
  int xx(abs(x-_x)), yy(abs(y-_y)), zz(abs(z-_z));
  if (xx > yy && xx > zz) {
    x = -y-z;
  } else if (yy > zz) {
    y = -x-z;
  } else {
    z = -x-y;
  }
  pos._x = x,pos. _y = y,pos. _z = z;
  return pos;
}

std::string FlatHexPosition::toString() const {
  return "HexPos[" + systemString(_type) + ":(" 
      + std::to_string(_x) + "," 
      + std::to_string(_y) + ","
      + std::to_string(_z) + ")]";
}
std::string FlatHexPosition::systemString(System s) {
  switch(s) {
  case OddQOffset:
    return "OddQOffset";
  case Axial:
    return "Axial";
  case Cubic:
    return "Cubic";
  case Grid:
    return "Grid";
  default:
    assert(0);
    return "";
  }
}