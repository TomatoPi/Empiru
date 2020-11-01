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
#include "Viewport.h"

#include "hex/Grid.h"
#include "hex/Conversion.h"

#include <cassert>
#include <cmath>

namespace gui {

const hex::Axial Viewport::VIEW_VX(1, -0.5);
const hex::Axial Viewport::VIEW_VY(0, 1);

/// \brief Constructor
/// \param tileWidth  : Tile's width in pixel on viewport
/// \param tileHeight : Tile's height in pixel on viewport
/// \param viewWidth  : View's width in pixel
/// \param viewHeight : View's height in pixel
Viewport::Viewport(int offsetX, int offsetY, int tileWidth, int tileHeight,
    int viewWidth, int viewHeight) noexcept :

    _tileWidth(tileWidth), _tileHeight(tileHeight), _offsetX(offsetX), _offsetY(
        offsetY), _viewWidth(viewWidth), _viewHeight(viewHeight),

    _viewport(
        hex::toAxial(
            hex::Grid(viewWidth * 2 / tileWidth, viewHeight / tileHeight))), _pos(),

    _vx(VIEW_VX), _vy(VIEW_VY),

    _rotation(hex::Identity), _antirotation(hex::Identity) {
  assert(0 < tileWidth);
  assert(0 < tileHeight);
  assert(0 < viewWidth);
  assert(0 < viewHeight);
}

/// \brief Convert a position on grid to a position on the screen
/// \param pos : position to convert
/// \param x : pixel column
/// \param y : pixel row
Pixel Viewport::toPixel(const hex::Axial &pos) const noexcept {
  hex::Axial res((pos - _pos) * _rotation + _viewport);
  hex::Grid g(hex::toGrid(res));
  return Pixel(_offsetX + 0.25 * g._x * _tileWidth,
      _offsetY + 0.5 * g._y * _tileHeight);
}
/// \brief Convert a position on the screen to position in grid
hex::Axial Viewport::fromPixel(const Pixel &pix) const noexcept {
  float xx = (pix._x - _offsetX) * 4. / _tileWidth;
  float yy = (pix._y - _offsetY) * 2. / _tileHeight;
  return _pos + (hex::toAxial(hex::Grid(xx, yy)) - _viewport) * _antirotation;
}

/// \brief return tile's width on viewport
int Viewport::tileHeight() const noexcept {
  return _tileHeight;
}
/// \brief return tile's height on viewport
int Viewport::tileWidth() const noexcept {
  return _tileWidth;
}
Pixel Viewport::tileSize() const noexcept {
  return Pixel(_tileWidth, _tileHeight);
}
int Viewport::viewHeight() const noexcept {
  return _viewHeight;
}
int Viewport::viewWidth() const noexcept {
  return _viewWidth;
}
bool Viewport::isInView(const Pixel &pix) const noexcept {
  SDL_Rect view { _offsetX, _offsetY, _viewWidth, _viewHeight };
  SDL_Point pixel { pix._x, pix._y };
  return SDL_PointInRect(&pixel, &view);
}
bool Viewport::doesIntersect(const SDL_Rect &r) const noexcept {
  SDL_Rect view { _offsetX, _offsetY, _viewWidth, _viewHeight };
  return SDL_HasIntersection(&view, &r);
}

/// \brief Compute the position of viewport's upLeftCorner
/// \param res : result in Axial coordinate system
hex::Axial Viewport::upLeftCorner() const noexcept {
  return _pos - _viewport * _rotation;
}

/// \brief Return Viewport's x and y vectors in Axis cs
Viewport::ViewAxices Viewport::viewPortAxis() const noexcept {
  return ViewAxices { .vx = _vx, .vy = _vy };
}

/// \brief return camera's targeted position
const hex::Axial& Viewport::target() const noexcept {
  return _pos;
}
/// \brief set camera's targeted position
void Viewport::target(const hex::Axial &pos) noexcept {
  _pos = pos;
  Subject<Events::ViewportMoved>::notify(); // @suppress("Function cannot be resolved")
}

/// \brief return camera's rotation matrix
const hex::Matrix& Viewport::rotation() const noexcept {
  return _rotation;
}
/// \brief set camera's rotation matrix
void Viewport::rotation(const hex::Matrix &m) noexcept {
  _rotation = m;
  _antirotation = m.inverse();
  _vx = VIEW_VX * m;
  _vy = VIEW_VY * m;
  Subject<Events::ViewportRotated>::notify(); // @suppress("Function cannot be resolved")
}

} /* namespace gui */
