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

/// \brief Constructor
/// \param tileWidth  : Tile's width in pixel on viewport
/// \param tileHeight : Tile's height in pixel on viewport 
/// \param viewWidth  : View's width in pixel
/// \param viewHeight : View's height in pixel 
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

/// \brief Convert a position on grid to a position on the screen
/// \param pos : position to convert
/// \parma x : pixel column
/// \param y : pixel row
void HexCamera::toPixel(const FlatHexPosition & pos, int *x, int *y) const {
  assert(x);
  assert(y);
  FlatHexPosition res(pos, FlatHexPosition::Axial);
  res = res + (_viewport * 0.5) - _pos;
  res.convert(FlatHexPosition::Grid);
  *x = 0.25 * res._x * _tileWidth;
  *y = 0.5 * res._y * _tileHeight;
}
/// \brief Convert a position on grid to position of it center on the screen
/// \param pos : position to convert
/// \parma x : pixel column
/// \param y : pixel row
void HexCamera::tileCenter(const FlatHexPosition & pos, int *x, int *y) const {
  assert(x);
  assert(y);
  FlatHexPosition res(pos, FlatHexPosition::Axial);
  res = res + (_viewport * 0.5) - _pos;
  res._x = (int)res._x;
  res._y = (int)res._y;
  res.convert(FlatHexPosition::Grid);
  *x = 0.25 * (res._x - 2) * _tileWidth;
  *y = 0.5 * (res._y - 1) * _tileHeight;
}

/// \brief return tile's width on viewport  
int HexCamera::tileHeight() const {
  return _tileHeight;
}
/// \brief return tile's height on viewport
int HexCamera::tileWidth() const {
  return _tileWidth;
}

/// \brief return camera's targeted position
const FlatHexPosition & HexCamera::target() const {
  return _pos;
}
/// \brief set camera's targeted position
void HexCamera::target(const FlatHexPosition & pos) {
  _pos = pos;
}

/// \brief Compute the position of viewport's upLeftCorner
/// \param res : result in Axial coordinate system
void HexCamera::upLeftCorner(FlatHexPosition *p) {
  assert(p);
  *p = _pos - _viewport * 0.5;
}
/// \brief Return Viewport's x and y vectors in Axis cs
void HexCamera::viewPortAxis(FlatHexPosition *x, FlatHexPosition *y) {
  *x = FlatHexPosition(1, -0.5, FlatHexPosition::Axial);
  *y = FlatHexPosition(0, 1, FlatHexPosition::Axial);
}