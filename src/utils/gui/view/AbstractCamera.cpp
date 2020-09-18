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

#include "AbstractCamera.h"


AbstractCamera::AbstractCamera(float hs, float vs, int nors) :
  _hScrollSpeed(hs),
  _vScrollSpeed(vs),
    
  _scrollH(0),
  _scrollV(0),
    
  _orientation(0),
  _nors(nors)
{
  
}

void AbstractCamera::scrollLeft() {
  _scrollH = -_hScrollSpeed;
}
void AbstractCamera::scrollRight() {
  _scrollH = _hScrollSpeed;
}
void AbstractCamera::stopLRScroll() {
  _scrollH = 0;
}

void AbstractCamera::scrollUp() {
  _scrollV = -_vScrollSpeed;
}
void AbstractCamera::scrollDown() {
  _scrollV = _vScrollSpeed;
}
void AbstractCamera::stopUDScroll() {
  _scrollV = 0;
}

void AbstractCamera::update() {
  if (_scrollH) {
    this->doUpdateLRScroll(_scrollH);
  }
  if (_scrollV) {
    this->doUpdateUDScroll(_scrollV);
  }
}

int AbstractCamera::getOrientation() {
  return _orientation;
}

void AbstractCamera::rotateRight() {
  _orientation = (_orientation <= 0 ? _nors : _orientation) -1;
  this->doRotateRight();
}

void AbstractCamera::rotateLeft() {
  _orientation = (_orientation+1) %_nors;
  this->doRotateLeft();
}