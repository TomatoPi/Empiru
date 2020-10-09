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
/// \file   PeonController.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 07:46
///

#ifndef PEONCONTROLLER_H
#define PEONCONTROLLER_H

#include "controller/core/EntityControllerInterface.h"
#include "controller/core/GameControllerInterface.h"

class PeonController : public EntityControllerInterface {
private:
  
  GameControllerInterface& _controller;
  
public:
  
  PeonController(GameControllerInterface& controller) noexcept :
    _controller(controller)
  {
  }
  
  virtual void leftClickOn(EntityPtr ptr) noexcept override;
  virtual void leftClickOut(EntityPtr ptr) noexcept override;
  virtual void RightClickOn(EntityPtr ptr) noexcept override;
  virtual void RightClickOut(EntityPtr ptr) noexcept override;
  virtual void cursorMoved() noexcept override;
  virtual void deselected(EntityPtr ptr) noexcept override;
};

#endif /* PEONCONTROLLER_H */
