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
/// \file   Engine.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 12 septembre 2020, 08:51
/// \brief Core object for user control
///

#ifndef ENGINE_H
#define ENGINE_H

#include "world/World.h"
#include "controller/CtrlState.h"

/// \brief Main handler for user control
/// \todo Nettoyer le code
class Controller {
private:
  
  World           *_world; ///< THA WORLDOOOOO
  ControllerState _state;  ///< The game controller
  
public:
  
  /// \brief Constructor
  Controller(World *w);
  
  /// \brief Called when a left click is performed at given position
  void leftClickAt(const FlatHexPosition & click);
  /// \brief Called when a right click is performed at given position
  void rightClickAt(const FlatHexPosition & click);
};

#endif /* ENGINE_H */
