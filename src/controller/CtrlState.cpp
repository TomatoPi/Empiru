/*
 * Copyright (C) 2020 Alexis
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
/// \file   CtrlState.cpp
/// \author Alexis CORREIA HENRIQUES <alex2ikangame@gmail.com>
///
/// \date 10 septembre 2020, 17:18
///

#include <cassert>

#include "CtrlState.h"
#include "selection/SelectedPeon.h"

/// \brief Constructor
ControllerState::ControllerState(
            WorldInterface & w, 
            GameEngine & g, 
            RenderingEngine & rdr) :
  _selectedPeon(nullptr),
  _selectionTracker(nullptr),
  _world(w),
  _gameEngine(g),
  _rdrEngine(rdr)
{
  
}

/// \brief Select given peon
void ControllerState::selectPeon(WorldRef * peon) {
  assert(peon);
  if (_selectedPeon) {
    deselectPeon();
  }
  _selectedPeon = peon;
  // Create the utility object for rendering selection
  _selectionTracker = _gameEngine.createObject(typeid(SelectedPeon));
  SelectedPeon & sel(static_cast<SelectedPeon &>(**_selectionTracker));
  sel._peon = peon;
  _rdrEngine.addTarget(_selectionTracker);
  _world.addObject(_selectionTracker);
}
/// \brief Clear selection
void ControllerState::deselectPeon() {
  if (_selectionTracker) {
    _world.removeObject(_selectionTracker);
    _rdrEngine.removeTarget(_selectionTracker);
    _gameEngine.removeObject(_selectionTracker);
  }
  _selectedPeon = nullptr;
  _selectionTracker = nullptr;
}

/// \brief Return selected peon or nullptr if no selection
WorldRef * ControllerState::selectedPeon() {
  return _selectedPeon;
}