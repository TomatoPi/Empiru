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
/// \brief Effective implementation of in-game camera
///
#include <control/impl/CameraCtrlCtrl.h>
#include <hex/Consts.h>
#include <hex/Conversion.h>

namespace ctrl {
namespace impl {

/// \brief Constructor of Concrete camera
///
/// \param offsetX    : View's up left corner X
/// \param offsetY    : View's up left corner Y
/// \param tileWidth    : Tile's width on screen  (px) 
/// \param tileHeight   : Tile's height on screen (px)
/// \param viewWidth    : View's width            (px)
/// \param viewHeight   : View's height           (px)
/// \param worldWidth   : World's width           (tile)
/// \param worldHeight  : World's height          (tile)
CameraCtrl::CameraCtrl(int wwidth, int wheight, gui::Viewport &view) noexcept :
    ACameraCtrl(0.1, 0.08, 6), _viewport(view), _vx(view.viewPortAxis().vx), _vy(
        view.viewPortAxis().vy), _worldWidth(wwidth), _worldHeight(wheight) {
}

/// \brief Must scroll the camera Horizontaly at given speed
void CameraCtrl::doUpdateLRScroll(float v) noexcept {
  hex::Axial pos = _viewport.target() + _vx * v;
  hex::Grid tmp(hex::toGrid(pos));
  if (tmp._x < 0) {
    tmp._x = 0;
  } else if (_worldWidth * 3 < (tmp._x + 3)) {
    tmp._x = _worldWidth * 3 - 3;
  }
  _viewport.target(hex::toAxial(tmp));
}
/// \brief Must scroll the camera verticaly at given speed
void CameraCtrl::doUpdateUDScroll(float v) noexcept {
  hex::Axial pos = _viewport.target() + _vy * v;
  hex::Grid tmp(hex::toGrid(pos));
  if (tmp._y < 0) {
    tmp._y = 0;
  } else if (_worldHeight * 2 < (tmp._y + 2)) {
    tmp._y = _worldHeight * 2 - 2;
  }
  _viewport.target(hex::toAxial(tmp));
}
/// \brief Must rotate camera to the left (clockwise)
void CameraCtrl::doRotateLeft() noexcept {
  _vx = _vx * hex::RMatrix_CC60A;
  _vy = _vy * hex::RMatrix_CC60A;
  _viewport.rotation(hex::RMatrix_C60A * _viewport.rotation());
}
/// \brief Must rotate camera to the right (anti-clockwise)
void CameraCtrl::doRotateRight() noexcept {
  _vx = _vx * hex::RMatrix_C60A;
  _vy = _vy * hex::RMatrix_C60A;
  _viewport.rotation(hex::RMatrix_CC60A * _viewport.rotation());
}

}  // namespace impl
}  // namespace gui
