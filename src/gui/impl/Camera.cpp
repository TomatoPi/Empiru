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
/// \file   Camera.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 11 septembre 2020, 17:13
///

#include "Camera.h"

/// \brief Constructor of Concrete camera
Camera::Camera(
    int tileWidth, int tileHeight, 
    int viewWidth, int viewHeight,
    int worldWidth, int worldHeight) : 
  CameraInterface(0.1, 0.05, 6),
  HexViewport(tileWidth, tileHeight, viewWidth, viewHeight),
  _worldWidth(worldWidth),
  _worldHeight(worldHeight),
  _vx(VIEW_VX),
  _vy(VIEW_VY)
{
}

/// \brief Must scroll the camera Horizontaly at given speed
void Camera::doUpdateLRScroll(float v) {
  FlatHexPosition pos = target() + _vx * v;
  pos.convert(FlatHexPosition::Grid);
  if (pos._x < 0) {
    pos._x = 0;
  } else if (_worldWidth*3 < (pos._x+3)) {
    pos._x = _worldWidth*3 -3;
  }
  target(pos.convert(FlatHexPosition::Axial));
}
/// \brief Must scroll the camera verticaly at given speed
void Camera::doUpdateUDScroll(float v) {
  FlatHexPosition pos = target() + _vy * v;
  pos.convert(FlatHexPosition::Grid);
  if (pos._y < 0) {
    pos._y = 0;
  } else if (_worldHeight*2 < (pos._y+2)) {
    pos._y = _worldHeight*2 -2;
  }
  target(pos.convert(FlatHexPosition::Axial));
}
/// \brief Must rotate camera to the left (clockwise)
void Camera::doRotateLeft() {
  _vx = _vx * ROTATE_RIGHT;
  _vy = _vy * ROTATE_RIGHT;
  rotation(ROTATE_LEFT * rotation());
}
/// \brief Must rotate camera to the right (anti-clockwise)
void Camera::doRotateRight() {
  _vx = _vx * ROTATE_LEFT;
  _vy = _vy * ROTATE_LEFT;
  rotation(ROTATE_RIGHT * rotation());
}