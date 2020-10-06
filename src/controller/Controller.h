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
/// \file   Controller.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 12 septembre 2020, 08:51
/// \brief Core object for user control
///

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "utils/engine/Observer.h"
#include "utils/world/WorldInterface.h"
#include "utils/world/WorldPtr.h"
#include "engine/GameEngine.h"
#include "entity/peon/Peon.h"

/// \brief Main handler for user control
class Controller : public Subject {
private:
  
  WorldInterface& _world;           ///< THA WORLDOOOOO
  GameEngine&     _engine;          ///< The Core of the GAMEUUH
  
  WorldPtr        _selection;       ///< The selected Object
  WorldObject::Position _cursor;    ///< Cursor position
  
public:
  
  /// \brief Constructor
  Controller(WorldInterface& w, GameEngine& engine) noexcept;
  
  /// \brief Called when a left click is performed at given position
  void leftClickOn(const WorldObject::Position& click, WorldPtr& obj);
  /// \brief Called when a right click is performed at given position
  void rightClickOn(const WorldObject::Position& click, WorldPtr& obj);
  
  /// \brief Called when a building has been selected
  void selectConstructionGhost(const std::type_info& type);
  
  /// \brief Called when the mouse has moved, maximum one time at each frame
  ///   Only the last position is passed to this function
  void cursorMoved(const WorldObject::Position& click, int x, int y);
  
  /// \brief Return the current position of the cursor
  const WorldObject::Position& cursor() const noexcept;
  
private:
  
  void peonRightClick(
    Peon* peon, 
    const WorldObject::Position& click, 
    WorldPtr& ptr);
};

#endif /* CONTROLLER_H */
