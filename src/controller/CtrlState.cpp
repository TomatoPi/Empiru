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

/// \brief Constructor
ControllerState::ControllerState() : _selectedPeon(nullptr)
{
  
}

/// \brief Select given peon
void ControllerState::selectPeon(Peon * peon) {
  assert(peon);
  _selectedPeon = peon;
}
/// \brief Clear selection
void ControllerState::deselectPeon() {
  _selectedPeon = nullptr;
}

/// \brief Return selected peon or nullptr if no selection
Peon * ControllerState::selectedPeon(){
  return _selectedPeon;
}