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

HexCamera::HexCamera(
    int tileWidth, int tileHeight, 
    int viewWidth, int viewHeight) :
  _tileWidth(tileWidth),
  _tileHeight(tileHeight),
  _viewport(viewWidth, viewHeight, tileWidth, tileHeight, FlatHexPosition::Axial),
  _pos(FlatHexPosition::Axial)
{
  assert(0 < tileWidth);
  assert(0 < tileHeight);
  assert(0 < viewWidth);
  assert(0 < viewHeight);
}

void HexCamera::toPixel(const FlatHexPosition & pos, int *x, int *y) const {
  assert(x);
  assert(y);
  FlatHexPosition res(pos, Axial);
  res = res + (_viewport * 0.5) - _pos;
  res.convert(FlatHexPosition::Grid);
  *x = res._x * _tileWidth;
  *y = res._y * _tileHeight;
}

int HexCamera::tileHeight() const {
  return _tileHeight;
}
int HexCamera::tileWidth() const {
  return _tileWidth;
}

const FlatHexPosition & HexCamera::target() const {
  return _pos;
}
void HexCamera::target(const FlatHexPosition & pos) {
  _pos = pos;
}

void HexCamera::upLeftCorner(FlatHexPosition *p) {
  assert(p);
  *p = _pos - _viewport * 0.5;
}