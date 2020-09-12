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
/// \date 11 septembre 2020, 17:15
///

#include "CameraInterface.h"


CameraInterface::CameraInterface(float hs, float vs, int nors) :
  _hScrollSpeed(hs),
  _vScrollSpeed(vs),
    
  _scrollH(0),
  _scrollV(0),
    
  _orientation(0),
  _nors(nors)
{
  
}

void CameraInterface::scrollLeft() {
  _scrollH = -_hScrollSpeed;
}
void CameraInterface::scrollRight() {
  _scrollH = _hScrollSpeed;
}
void CameraInterface::stopLRScroll() {
  _scrollH = 0;
}

void CameraInterface::scrollUp() {
  _scrollV = -_vScrollSpeed;
}
void CameraInterface::scrollDown() {
  _scrollV = _vScrollSpeed;
}
void CameraInterface::stopUDScroll() {
  _scrollV = 0;
}

void CameraInterface::update() {
  if (_scrollH) {
    this->doUpdateLRScroll(_scrollH);
  }
  if (_scrollV) {
    this->doUpdateUDScroll(_scrollV);
  }
}

int CameraInterface::getOrientation() {
  return _orientation;
}

void CameraInterface::rotateRight() {
  _orientation = (_orientation+1) %_nors;
  this->doRotateRight();
}

void CameraInterface::rotateLeft() {
  _orientation = (_orientation <= 0 ? _nors : _orientation) -1;
  this->doRotateLeft();
}