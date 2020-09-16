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
/// \file   Engine.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 12 septembre 2020, 08:51
/// \brief Core object for user control
///

#include "Controller.h"

#include "utils/log.h"
#include <cmath>

/// \brief Constructor
Controller::Controller(World *w) :
  _world(w), _state()
{
  
}
  
/// \brief Called when a left click is performed at given position
void Controller::leftClickAt(const FlatHexPosition & click) {
  
  auto content = _world->getContentAt(click);
  
  if (content != nullptr){
    for (auto peon : *content){
      FlatHexPosition tmp_pos(peon->pos(),FlatHexPosition::Grid);
      if (
          (fabs(click._x - tmp_pos._x) < 0.25) 
          && (fabs(click._y + 0.25 - tmp_pos._y) < 0.25)) 
      {
        _state.selectPeon(peon);
      } else {
        _state.deselectPeon();
      }
     }
  } else {
    _state.deselectPeon();
  }
}
/// \brief Called when a right click is performed at given position
void Controller::rightClickAt(const FlatHexPosition & click) {
  //Attention, il faudra vérifier si la position est clickable
  if (_state.selectedPeon() != nullptr){
    _state.selectedPeon()->setTargetPos(click);
  }
}