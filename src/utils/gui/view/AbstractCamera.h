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

#ifndef GUI_ABSTRACT_CAMERA_H
#define GUI_ABSTRACT_CAMERA_H

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
  
  /// \brief Start scroll to left
  void scrollLeft() noexcept  {
    _scrollH = -_hScrollSpeed;
  }
  /// \brief Start scroll to right
  void scrollRight() noexcept  {
    _scrollH = _hScrollSpeed;
  }
  /// \brief Stop Left or Right scrolling
  void stopLRScroll() noexcept  {
    _scrollH = 0;
  }
  
  /// \brief Start scroll up
  void scrollUp() noexcept {
    _scrollV = -_vScrollSpeed;
  }
  /// \brief  Start scroll down
  void scrollDown() noexcept {
    _scrollV = _vScrollSpeed;
  }
  /// \brief Stop Up or Down scrolling
  void stopUDScroll() noexcept {
    _scrollV = 0;
  }
  
  /// \brief Update camera position according to scroll
  void update() noexcept {
    if (_scrollH) {
      this->doUpdateLRScroll(_scrollH);
    }
    if (_scrollV) {
      this->doUpdateUDScroll(_scrollV);
    }
  }
  
  /// \brief Rotation of 60° to the right
  void rotateRight() noexcept {
    _orientation = (_orientation <= 0 ? _nors : _orientation) -1;
    this->doRotateRight();
  }
  /// \brief Rotation of 60° to the left
  void rotateLeft() noexcept {
    _orientation = (_orientation+1) %_nors;
    this->doRotateLeft();
  }
  
  /// \brief Get the camera orientation in [0,_nors[
  int getOrientation() const noexcept {
    return _orientation;
  }
  
protected:
  
  /// \brief Create an Abstract camera
  /// \param hs : Horizontal scroll speed
  /// \param vs : Vertical scroll speed
  /// \param nors : Count of available orientations
  AbstractCamera(float hs, float vs, int nors) noexcept :
    _hScrollSpeed(hs), _vScrollSpeed(vs),
    _scrollH(0), _scrollV(0),
    _orientation(0), _nors(nors)
  {
  } 
  
  /// \brief Must scroll the camera Horizontaly at given speed
  virtual void doUpdateLRScroll(float v) noexcept = 0;
  /// \brief Must scroll the camera verticaly at given speed
  virtual void doUpdateUDScroll(float v) noexcept = 0;
  /// \brief Must rotate camera to the left (clockwise)
  virtual void doRotateLeft() noexcept = 0;
  /// \brief Must rotate camera to the right (anti-clockwise)
  virtual void doRotateRight() noexcept = 0;
};

#endif /* GUI_ABSTRACT_CAMERA_H */
