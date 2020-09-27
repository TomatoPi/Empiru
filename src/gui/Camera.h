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

#ifndef CAMERA_H
#define CAMERA_H

#include "utils/hex/Viewport.h"
#include "utils/gui/view/AbstractCamera.h"

/// \brief Effective implementation of in-game camera
class Camera : public AbstractCamera, public hex::Viewport {
private:
  
  int _worldWidth;  ///< World's width in tile count
  int _worldHeight; ///< World height in tile count
  
  hex::Axial _vx; ///< Camera's motion X vector
  hex::Axial _vy; ///< Camera's motion Y vector
  
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
  Camera(
    int offsetX, int offsetY,
    int tileWidth, int tileHeight, 
    int viewWidth, int viewHeight,
    int worldWidth, int worldHeight);
  
protected:
  
  /// \brief Must scroll the camera Horizontaly at given speed
  virtual void doUpdateLRScroll(float v) noexcept ;
  /// \brief Must scroll the camera verticaly at given speed
  virtual void doUpdateUDScroll(float v) noexcept ;
  /// \brief Must rotate camera to the left (clockwise)
  virtual void doRotateLeft() noexcept ;
  /// \brief Must rotate camera to the right (anti-clockwise)
  virtual void doRotateRight() noexcept ;
};

#endif /* CAMERA_H */
