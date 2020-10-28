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
/// \file   Camera.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 11 septembre 2020, 17:13
/// \brief Effective implementation of in-game camera
///
#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <control/ACameraCtrlCtrl.h>
#include "gui/Viewport.h"

namespace ctrl {
namespace impl {

/// \brief Effective implementation of in-game camera
class CameraCtrl final: public ACameraCtrl {
private:

  gui::Viewport& _viewport;

  hex::Axial _vx; ///< Camera's motion X vector
  hex::Axial _vy; ///< Camera's motion Y vector

  int _worldWidth;  ///< World's width in tile count
  int _worldHeight; ///< World height in tile count

public:

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
  CameraCtrl(int wwidth, int wheight, gui::Viewport& view) noexcept;

  virtual ~CameraCtrl() noexcept = default;

protected:

  /// \brief Must scroll the camera Horizontaly at given speed
  void doUpdateLRScroll(float v) noexcept override;
  /// \brief Must scroll the camera verticaly at given speed
  void doUpdateUDScroll(float v) noexcept override;
  /// \brief Must rotate camera to the left (clockwise)
  void doRotateLeft() noexcept override;
  /// \brief Must rotate camera to the right (anti-clockwise)
  void doRotateRight() noexcept override;
};

}  // namespace impl
}  // namespace gui

#endif /* CAMERA_CONTROLLER_H */
