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

#include "../IGameCtrl.h"
#include "../IEntityCtrl.h"

#include <game/Decorator.h>
#include <alloc/impl/WrapHandle.h>
#include <unordered_map>

namespace ctrl {

IGameCtrl *IGameCtrl::_instance = nullptr;

namespace impl {

struct SelectHandleDecorator : public game::Decorator {
  game::EUID uid;
  SelectHandleDecorator() noexcept;
  virtual ~SelectHandleDecorator() noexcept = default;
  static const Kind TypeID() noexcept;
};

/// \brief Main handler for user control
class Controller: public IGameCtrl {
private:

  typedef std::unordered_map<game::EUID::Kind, IEntityCtrl*> ControlTable; // @suppress("Invalid template argument")

  ControlTable _controllers; ///< Table of objects specific controllers
  game::EUID _selection;   ///< The selected Object
  world::Position _cursor;      ///< Cursor position
  game::Decorator::Pointer _selectDecorator;

public:

  /// \brief Constructor
  Controller() noexcept;

  void selectObject(const game::EUID uid) noexcept override;
  void deselectObject(const game::EUID uid) noexcept override;
  const game::EUID& selection() const noexcept override;
  /// \brief Return the current position of the cursor
  const world::Position& cursor() const noexcept override;

  /// \brief Called when a left click is performed at given position
  void leftClickOn(const world::Position &click, const game::EUID uid) noexcept;
  /// \brief Called when a right click is performed at given position
  void rightClickOn(const world::Position &click, const game::EUID uid) noexcept;
  /// \brief Called when the mouse has moved, maximum one time at each frame
  ///   Only the last position is passed to this function
  void cursorMoved(const world::Position &click, int x, int y) noexcept;

  void registerEntityController(const game::EUID::Kind kind,
      IEntityCtrl *&&controller) noexcept;

private :

  IEntityCtrl& get(const game::EUID uid) noexcept;
};

}  // namespace impl

}  // namespace ctrl

#endif /* CONTROLLER_H */
