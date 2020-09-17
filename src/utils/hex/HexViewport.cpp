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

#include "HexViewport.h"
#include "utils/log.h"

const Matrix22 HexViewport::ROTATE_LEFT(0, -1, 1, 1);
const Matrix22 HexViewport::ROTATE_RIGHT(1, 1, -1, 0);
const FlatHexPosition HexViewport::VIEW_VX(1, -0.5, FlatHexPosition::Axial);
const FlatHexPosition HexViewport::VIEW_VY(0, 1, FlatHexPosition::Axial);

/// \brief Constructor
/// \param tileWidth  : Tile's width in pixel on viewport
/// \param tileHeight : Tile's height in pixel on viewport 
/// \param viewWidth  : View's width in pixel
/// \param viewHeight : View's height in pixel 
/// \param worldWidth : World's width in tile count
/// \param worldHeight: World height in tile count
HexViewport::HexViewport(
    int tileWidth, int tileHeight, 
    int viewWidth, int viewHeight) :

  _tileWidth(tileWidth),
  _tileHeight(tileHeight),
    
  _viewport(viewWidth/2, viewHeight/2, tileWidth, tileHeight, FlatHexPosition::Axial),
  _pos(FlatHexPosition::Axial),
    
  _vx(VIEW_VX),
  _vy(VIEW_VY),
    
  _rotation(1, 0, 0, 1),
  _antirotation(1, 0, 0, 1)
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
void HexViewport::toPixel(const FlatHexPosition & pos, int *x, int *y) const {
  assert(x);
  assert(y);
  FlatHexPosition res(pos, FlatHexPosition::Axial);
  res = (res - _pos) * _rotation + _viewport;
  res.convertTo(FlatHexPosition::Grid);
  *x = 0.25 * res._x * _tileWidth;
  *y = 0.5 * res._y * _tileHeight;
}
/// \brief Convert a position on the screen to position in grid
void HexViewport::fromPixel(int x, int y, FlatHexPosition *pos) const {
  assert(pos);
  float xx = x * 4. / _tileWidth;
  float yy = y * 2. / _tileHeight;
  //LOG_WRN("%d,%d -> %f,%f\n", x, y, xx, yy);
  *pos = FlatHexPosition(xx, yy, FlatHexPosition::Grid);
  //LOG_WRN("%s\n", pos->toString().c_str());
  *pos = _pos + (*pos - _viewport) * _antirotation;
  //LOG_WRN("%s\n", pos->toString().c_str());
}

/// \brief return tile's width on viewport  
int HexViewport::tileHeight() const {
  return _tileHeight;
}
/// \brief return tile's height on viewport
int HexViewport::tileWidth() const {
  return _tileWidth;
}

/// \brief Compute the position of viewport's upLeftCorner
/// \param res : result in Axial coordinate system
void HexViewport::upLeftCorner(FlatHexPosition *p) const {
  assert(p);
  *p = _pos - _viewport * _rotation;
}
/// \brief Return Viewport's x and y vectors in Axis cs
void HexViewport::viewPortAxis(FlatHexPosition *x, FlatHexPosition *y) const {
  *x = _vx;
  *y = _vy;
}
const FlatHexPosition & HexViewport::viewportVX() const {
  return _vx;
}
const FlatHexPosition & HexViewport::viewportVY() const {
  return _vy;
}

/// \brief return camera's targeted position
const FlatHexPosition & HexViewport::target() const {
  return _pos;
}
/// \brief set camera's targeted position
void HexViewport::target(const FlatHexPosition & pos) {
  _pos = pos;
}

/// \brief return camera's rotation matrix
const Matrix22 & HexViewport::rotation() const {
  return _rotation;
}
/// \brief set camera's rotation matrix
void HexViewport::rotation(const Matrix22 & m) {
  _rotation = m;
  _antirotation = m.inverse();
  _vx = VIEW_VX * m;
  _vy = VIEW_VY * m;
  LOG_DEBUG("VX  : %s\n", _vx.toString().c_str());
  LOG_DEBUG("VY  : %s\n", _vy.toString().c_str());
  LOG_DEBUG("ROT :\n%6f %6f\n%6f %6f\n", _rotation._a, _rotation._b, _rotation._c, _rotation._d);
}

void HexViewport::rotatedAxialVectors(FlatHexPosition *ax, FlatHexPosition *ay) const {
  assert(ax);
  assert(ay);
  *ay = _vy;
  *ax = _vx + _vy * 0.5;
}