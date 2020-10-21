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
/// \file   GameControllerInterface.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 06:10
///

#ifndef GAMECONTROLLERINTERFACE_H
#define GAMECONTROLLERINTERFACE_H

#include "core/Pointer.h"
#include "world/core/Types.h"

class IGameController {
public:
  
  virtual void selectObject(core::Pointer ptr) noexcept = 0;
  virtual void deselectObject(core::Pointer ptr) noexcept = 0;
  virtual void objectAction(core::Pointer ptr, core::Pointer target) noexcept = 0;
  
  virtual const core::Pointer& selection() const noexcept = 0;
  virtual const world::Position& cursor() const noexcept = 0;
};

#endif /* GAMECONTROLLERINTERFACE_H */

