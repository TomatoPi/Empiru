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

#include <typeinfo>
#include <typeindex>
#include <unordered_map>

#include "utils/pattern/Observer.h"
#include "controller/core/GameControllerInterface.h"
#include "controller/core/EntityControllerInterface.h"
#include "engine/core/entity/EntityPtr.h"

/// \brief Main handler for user control
class Controller : 
  public GameControllerInterface, 
  public Subject, 
  public Observer 
{
private:
  
  typedef std::unordered_map<std::type_index,EntityControllerInterface*> 
    ControlTable;
  
  ControlTable          _controllers; ///< Table of objects specific controllers
  EntityPtr             _selection;   ///< The selected Object
  WorldObject::Position _cursor;      ///< Cursor position
  
public:
  
  /// \brief Constructor
  Controller() noexcept;
  
  virtual void selectObject(EntityPtr ptr) noexcept override;
  virtual void deselectObject(EntityPtr ptr) noexcept override;
  virtual void objectAction(EntityPtr ptr, EntityPtr target) noexcept override;
  virtual const EntityPtr& selection() const noexcept override;
  /// \brief Return the current position of the cursor
  virtual const WorldObject::Position& cursor() const noexcept override;
  
  /// \brief Called when a left click is performed at given position
  void leftClickOn(const WorldObject::Position& click, const EntityPtr& ptr);
  /// \brief Called when a right click is performed at given position
  void rightClickOn(const WorldObject::Position& click, const EntityPtr& ptr);
  /// \brief Called when the mouse has moved, maximum one time at each frame
  ///   Only the last position is passed to this function
  void cursorMoved(const WorldObject::Position& click, int x, int y);
  
  void registerController(
    const std::type_info& type, 
    EntityControllerInterface*&& controller) noexcept;
  
private:
  
  EntityControllerInterface& get(const EntityPtr& ptr) noexcept;
};

#endif /* CONTROLLER_H */
