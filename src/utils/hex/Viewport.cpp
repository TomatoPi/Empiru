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
/// \file   HexViewport.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 8 septembre 2020, 03:59
///

#include <cassert>
#include <cmath>

#include "Viewport.h"
#include "Grid.h"
#include "Conversion.h"
#include "utils/log.h"

namespace hex {

  const Axial Viewport::VIEW_VX(1, -0.5);
  const Axial Viewport::VIEW_VY(0, 1);

  /// \brief Constructor
  /// \param tileWidth  : Tile's width in pixel on viewport
  /// \param tileHeight : Tile's height in pixel on viewport 
  /// \param viewWidth  : View's width in pixel
  /// \param viewHeight : View's height in pixel
  Viewport::Viewport(
      int tileWidth, int tileHeight, 
      int viewWidth, int viewHeight) :

    _tileWidth(tileWidth),
    _tileHeight(tileHeight),

    _viewport(toAxial(Grid(viewWidth*2/tileWidth, viewHeight/tileHeight))),
    _pos(),

    _vx(VIEW_VX),
    _vy(VIEW_VY),

    _rotation(Identity),
    _antirotation(Identity)
  {
    assert(0 < tileWidth);
    assert(0 < tileHeight);
    assert(0 < viewWidth);
    assert(0 < viewHeight);
  }

  /// \brief Convert a position on grid to a position on the screen
  /// \param pos : position to convert
  /// \param x : pixel column
  /// \param y : pixel row
  void Viewport::toPixel(const Axial & pos, int *x, int *y) const {
    assert(x);
    assert(y);
    Axial res((pos - _pos) * _rotation + _viewport);
    Grid g(toGrid(res));
    *x = 0.25 * g._x * _tileWidth;
    *y = 0.5 * g._y * _tileHeight;
  }
  /// \brief Convert a position on the screen to position in grid
  void Viewport::fromPixel(int x, int y, Axial *pos) const {
    assert(pos);
    float xx = x * 4. / _tileWidth;
    float yy = y * 2. / _tileHeight;
    *pos = toAxial(Grid(xx, yy));
    *pos = _pos + (*pos - _viewport) * _antirotation;
  }

  /// \brief return tile's width on viewport  
  int Viewport::tileHeight() const {
    return _tileHeight;
  }
  /// \brief return tile's height on viewport
  int Viewport::tileWidth() const {
    return _tileWidth;
  }

  /// \brief Compute the position of viewport's upLeftCorner
  /// \param res : result in Axial coordinate system
  void Viewport::upLeftCorner(Axial *res) const {
    assert(res);
    *res = _pos - _viewport * _rotation;
  }

  /// \brief Return Viewport's x and y vectors in Axis cs
  void Viewport::viewPortAxis(Axial *x, Axial *y) const {
    *x = _vx;
    *y = _vy;
  }

  /// \brief return camera's targeted position
  const Axial & Viewport::target() const {
    return _pos;
  }
  /// \brief set camera's targeted position
  void Viewport::target(const Axial & pos) {
    _pos = pos;
  }

  /// \brief return camera's rotation matrix
  const Matrix & Viewport::rotation() const {
    return _rotation;
  }
  /// \brief set camera's rotation matrix
  void Viewport::rotation(const Matrix & m) {
    _rotation = m;
    _antirotation = m.inverse();
    _vx = VIEW_VX * m;
    _vy = VIEW_VY * m;
  }
}