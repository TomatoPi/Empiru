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

#include "controller/core/IGameController.h"
#include "controller/core/IEntityController.h"
#include "core/Pointer.h"
#include "core/Observer.h"

/// \brief Main handler for user control
class Controller : 
  public IGameController, 
  public core::Subject, 
  public core::Observer 
{
private:
  
  typedef std::unordered_map<std::type_index,IEntityController*> 
    ControlTable;
  
  ControlTable          _controllers; ///< Table of objects specific controllers
  core::Pointer             _selection;   ///< The selected Object
  world::Position _cursor;      ///< Cursor position
  
public:
  
  /// \brief Constructor
  Controller() noexcept;
  
  virtual void selectObject(core::Pointer ptr) noexcept override;
  virtual void deselectObject(core::Pointer ptr) noexcept override;
  virtual void objectAction(core::Pointer ptr, core::Pointer target) noexcept override;
  virtual const core::Pointer& selection() const noexcept override;
  /// \brief Return the current position of the cursor
  virtual const world::Position& cursor() const noexcept override;
  
  /// \brief Called when a left click is performed at given position
  void leftClickOn(const world::Position& click, const core::Pointer& ptr) noexcept;
  /// \brief Called when a right click is performed at given position
  void rightClickOn(const world::Position& click, const core::Pointer& ptr) noexcept;
  /// \brief Called when the mouse has moved, maximum one time at each frame
  ///   Only the last position is passed to this function
  void cursorMoved(const world::Position& click, int x, int y) noexcept;
  
  void registerController(
    const std::type_info& type, 
    IEntityController*&& controller) noexcept;
  
private:
  
  IEntityController& get(const core::Pointer& ptr) noexcept;
};

#endif /* CONTROLLER_H */
