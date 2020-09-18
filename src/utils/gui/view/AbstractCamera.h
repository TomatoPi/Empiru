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
/// \file   AbstractCamera.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 11 septembre 2020, 17:15
///

#ifndef ABSTRACTCAMERA_H
#define ABSTRACTCAMERA_H

/// \brief Abstract object used to control a viewport
class AbstractCamera {
private:
  
  float _hScrollSpeed; ///< Horizontal scroll speed
  float _vScrollSpeed; ///< Vertical scroll speed
  
  float _scrollH; ///< {<0,0<,0} Scroll Left, Right, None
  float _scrollV; ///< {<0,0<,0} scroll Up, Down, None
  
  int _orientation; ///< Camera's orientation
  int _nors;       ///< Count of available orientations
  
public:
  
  void scrollLeft();  ///< Start scroll to left
  void scrollRight(); ///< Start scroll to right
  void stopLRScroll();///< Stop Left or Right scrolling
  
  void scrollUp();    ///< Start scroll up
  void scrollDown();  ///< Start scroll down
  void stopUDScroll();///< Stop Up or Down scrolling
  
  void update(); ///< Update camera position according to scroll
  
  void rotateRight(); ///< Rotation of 60° to the right
  void rotateLeft(); ///< Rotation of 60° to the left
  
  int getOrientation() const; ///< Get the camera orientation in [0,_nors[
  
protected:
  
  /// \brief Create an Abstract camera
  /// \param hs : Horizontal scroll speed
  /// \param vs : Vertical scroll speed
  /// \param nors : Count of available orientations
  AbstractCamera(float hs, float vs, int nors);
  
  /// \brief Must scroll the camera Horizontaly at given speed
  virtual void doUpdateLRScroll(float v) = 0;
  /// \brief Must scroll the camera verticaly at given speed
  virtual void doUpdateUDScroll(float v) = 0;
  /// \brief Must rotate camera to the left (clockwise)
  virtual void doRotateLeft() = 0;
  /// \brief Must rotate camera to the right (anti-clockwise)
  virtual void doRotateRight() = 0;
};

#endif /* ABSTRACTCAMERA_H */
