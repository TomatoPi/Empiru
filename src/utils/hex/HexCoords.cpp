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

#include <cassert>

OQOffsetPosition::OQOffsetPosition() : _row(0), _col(0) {
  
}
OQOffsetPosition::OQOffsetPosition(float r, float c) : _row(r), _col(c) {
  
}
bool OQOffsetPosition::operator==(const OQOffsetPosition & a) const {
  return a._row == _row && a._col == _col;
}

GridPosition::GridPosition() : _w(0), _h(0) {
  
}

AxialPosition::AxialPosition() : _row(0), _col(0) {
  
}
AxialPosition::AxialPosition(float r, float c) : _row(r), _col(c) {
  
}

CubePosition::CubePosition() : _x(0), _y(0), _z(0) {
  
}

void convertPosition(
  const OQOffsetPosition & src, 
  GridPosition * dest)
{
  assert(dest);
  dest->_h = 2 * src._row + ((int)(src._col) & 1);
  dest->_w = 3 * src._col;
}

void convertPosition(
  const AxialPosition & src, 
  OQOffsetPosition *dest)
{
  assert(dest);
  dest->_col = src._col;
  dest->_row = src._row + (src._col - ((int)(src._col)&1)) / 2;
}