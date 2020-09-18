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
///

#ifndef CAMERA_H
#define CAMERA_H

#include "utils/hex/HexViewport.h"
#include "utils/gui/view/AbstractCamera.h"

class Camera : public AbstractCamera, public HexViewport {
private:
  
  int _worldWidth;  ///< World's width in tile count
  int _worldHeight; ///< World height in tile count
  
  FlatHexPosition _vx; ///< Camera's motion X vector
  FlatHexPosition _vy; ///< Camera's motion Y vector
  
public:
  
  /// \brief Constructor of Concrete camera
  /// \param worldWidth : World's width in tile count
  /// \param worldHeight: World height in tile count
  Camera(
    int tileWidth, int tileHeight, 
    int viewWidth, int viewHeight,
    int worldWidth, int worldHeight);
  
protected:
  
  /// \brief Must scroll the camera Horizontaly at given speed
  virtual void doUpdateLRScroll(float v);
  /// \brief Must scroll the camera verticaly at given speed
  virtual void doUpdateUDScroll(float v);
  /// \brief Must rotate camera to the left (clockwise)
  virtual void doRotateLeft();
  /// \brief Must rotate camera to the right (anti-clockwise)
  virtual void doRotateRight();
};

#endif /* CAMERA_H */
