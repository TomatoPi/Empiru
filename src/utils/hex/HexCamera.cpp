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
/// \param worldWidth : World's width in tile count
/// \param worldHeight: World height in tile count
HexCamera::HexCamera(
    int tileWidth, int tileHeight, 
    int viewWidth, int viewHeight,
    int worldWidth, int worldHeight) :

  _tileWidth(tileWidth),
  _tileHeight(tileHeight),
  _worldWidth(worldWidth),
  _worldHeight(worldHeight),
    
  _hScrollSpeed(0.5),
  _vScrollSpeed(0.1),
    
  _scrollH(0),
  _scrollV(0),
    
  _viewport(viewWidth, viewHeight, tileWidth, tileHeight, FlatHexPosition::Axial),
  _pos(FlatHexPosition::Axial),
    
  _vx(1, -0.5, FlatHexPosition::Axial),
  _vy(0, 1, FlatHexPosition::Axial)
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
/// \warning this function could cause error accumulation if result is stored and reused
void HexCamera::tileCenter(const FlatHexPosition & pos, int *x, int *y) const {
  assert(x);
  assert(y);
  FlatHexPosition res(pos, FlatHexPosition::Axial);
  res = res + (_viewport * 0.5) - _pos;
  // Prevent rounding error
  res._x = (int)(res._x + 0.00001);
  res._y = (int)(res._y + 0.00001);
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

/// \brief Compute the position of viewport's upLeftCorner
/// \param res : result in Axial coordinate system
void HexCamera::upLeftCorner(FlatHexPosition *p) {
  assert(p);
  *p = _pos - _viewport * 0.5;
}
/// \brief Return Viewport's x and y vectors in Axis cs
void HexCamera::viewPortAxis(FlatHexPosition *x, FlatHexPosition *y) {
  *x = _vx;
  *y = _vy;
}

/// \brief return camera's targeted position
const FlatHexPosition & HexCamera::target() const {
  return _pos;
}
/// \brief set camera's targeted position
void HexCamera::target(const FlatHexPosition & pos) {
  _pos = pos;
}

void HexCamera::scrollLeft() {
  _scrollH = -_hScrollSpeed;
}
void HexCamera::scrollRight() {
  _scrollH = _hScrollSpeed;
}
void HexCamera::stopLRScroll() {
  _scrollH = 0;
}

void HexCamera::scrollUp() {
  _scrollV = -_vScrollSpeed;
}
void HexCamera::scrollDown() {
  _scrollV = _vScrollSpeed;
}
void HexCamera::stopUDScroll() {
  _scrollV = 0;
}

void HexCamera::update() {
  if (_scrollH) {
    FlatHexPosition pos = _pos + _vx * _scrollH;
    pos.convert(FlatHexPosition::OddQOffset);
    if (pos._x < 0) {
      pos._x = 0;
    } else if (_worldWidth < (pos._x - 1)) {
      pos._x = _worldWidth -1;
    }
    _pos = pos.convert(FlatHexPosition::Axial);
  }
  if (_scollV) {
    FlatHexPosition pos = _pos + _vy * _scrollV;
    pos.convert(FlatHexPosition::OddQOffset);
    if (pos._y < 0) {
      pos._y = 0;
    } else if (_worldHeight < (pos._y - 1)) {
      pos._y = _worldHeight -1;
    }
    _pos = pos.convert(FlatHexPosition::Axial);
  }
}