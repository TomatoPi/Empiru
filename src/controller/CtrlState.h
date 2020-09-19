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
/// \file   CtrlState.h
/// \author Alexis CORREIA HENRIQUES <alex2ikangame@gmail.com>
///
/// \date 10 septembre 2020, 17:18
/// \brief Provide state machine for game controller
///

#ifndef CONTROLLERSTATE_H
#define CONTROLLERSTATE_H

#include <SDL2/SDL_events.h>
#include "utils/engine/WorldRef.h"

/// \brief Object used to keep state of game controller
class ControllerState {
  private:
    
    WorldRef * _selectedPeon; ///< Obvious
  
  public:
     
    /// \brief Constructor
    ControllerState();
    
    /// \brief Select given peon
    void selectPeon(WorldRef * peon);
    /// \brief Clear selection
    void deselectPeon();
    
    /// \brief Return selected peon or nullptr if no selection
    WorldRef * selectedPeon();
};

#endif /* CONTROLLERSTATE_H */
