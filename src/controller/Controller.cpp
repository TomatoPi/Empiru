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
/// \file   Controller.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 12 septembre 2020, 08:51
/// \brief Core object for user control
///

#include "Controller.h"

#include "entity/peon/Peon.h"
#include "utils/log.h"
#include <cmath>

/// \brief Constructor
Controller::Controller(WorldInterface & w) :
  _world(w), _state()
{
  
}
  
/// \brief Called when a left click is performed at given position
void Controller::leftClickAt(const FlatHexPosition & click) {
  
  WorldRef *selection(nullptr);
  // Search for a peon near click
  /// \todo might be slow if there is a great amount of objects near click
  click.convert(FlatHexPosition::Grid).mapNeightbours(
    [&]
    (const FlatHexPosition & pos) -> bool 
    {
      auto content = _world.getContentAt(pos);
      if (content != nullptr){
        for (auto obj : *content){
          if (typeid(**obj) != typeid(Peon)) continue;
          const Peon & peon(static_cast<const Peon &>(**obj));
          FlatHexPosition tmp(peon.pos(), FlatHexPosition::Grid);
          if (
              (fabs(click._x - tmp._x) < 0.25) 
              && (fabs(click._y + 0.25 - tmp._y) < 0.25)) 
          {
            selection = obj;
            return true;
          }
        }
      }
      return false;
    });
  // Update controller according to result
  if (selection) {
    _state.selectPeon(selection);
  } else {
    _state.deselectPeon();
  }
}
/// \brief Called when a right click is performed at given position
void Controller::rightClickAt(const FlatHexPosition & click) {
  
  // If there is a selected peon and click is valid, let's go
  if (_state.selectedPeon() != nullptr && _world.isOnMap(click)) {
    Peon & peon(static_cast<Peon &>(**_state.selectedPeon()));
    peon.clearPath();
    peon.addStep(click);
    peon.beginStep();
  }
}