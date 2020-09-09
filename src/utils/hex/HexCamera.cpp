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
/// \file   HexCamera.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 8 septembre 2020, 03:59
///

#include <cassert>
#include <cmath>

#include "HexCamera.h"
#include "utils/log.h"

HexCamera::HexCamera(int tileWidth, int tileHeight) :
  _tileWidth(tileWidth),
  _tileHeight(tileHeight)
{
  assert(0 < tileWidth);
  assert(0 < tileHeight);
}

void HexCamera::toPixel(const GridPosition & pos, int *x, int *y) const {
  assert(x);
  assert(y);
  
  GridPosition g;
  OQOffsetPosition oqo;
  
  convertPosition(_pos, &oqo);
  convertPosition(oqo, &g);
  
  g._h += pos._h;
  g._w += pos._w;
  
  // GridPosition(0,0) take place at the center of tile (0,0)
  // An offset is added to put this point at screen's top left corner
  *x = (g._w - 2) * _tileWidth * 0.25;
  *y = (g._h - 1) * _tileHeight * 0.5;
}

int HexCamera::tileHeight() const {
  return _tileHeight;
}
int HexCamera::tileWidth() const {
  return _tileWidth;
}

const AxialPosition & HexCamera::target() const {
  return _pos;
}
void HexCamera::target(const AxialPosition & pos) {
  _pos = pos;
}

void HexCamera::upLeftCorner(
  int vWidth, int vHeight, 
  OQOffsetPosition *p) 
{
  assert(p);
  // Screen diagonal vector is converted to Axial vector
  // Then standard vector addition is used to translate the camera
  AxialPosition tmp;
  axialFromPixel(vWidth, vHeight, &tmp);
  LOG_DEBUG("Screen : %f,%f\n", tmp._row, tmp._col);
  tmp._col = _pos._col - tmp._col / 2;
  tmp._row = _pos._row - tmp._row / 2;
  LOG_DEBUG("Camera : %f,%f\n", tmp._row, tmp._col);
  convertPosition(tmp, p);
}

void HexCamera::axialToPixel(const AxialPosition & pos, int *x, int *y) const {
  assert(x);
  assert(y);
  *x = _tileWidth * 1.5 * pos._col;
  *y = _tileHeight * sqrt(3) * (pos._col/2. + pos._row);
}

void HexCamera::axialFromPixel(int x, int y, AxialPosition *pos) const {
  assert(pos);
  // y is scaled according to tile's geometry
  float z = y * sqrt(3) * 0.5 * _tileWidth / _tileHeight;
  LOG_DEBUG("%d, %f\n", y, z);
  pos->_col = 4 * x / (3. * _tileWidth);
  pos->_row = 2 * (sqrt(3) * z - x) / (3. * _tileWidth);
}