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
/// \file   EntityController.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 05:43
///

#ifndef ENTITYCONTROLLER_H
#define ENTITYCONTROLLER_H

#include "engine/core/entity/EntityPtr.h"

class EntityControllerInterface {
public:
  
  virtual void leftClickOn(EntityPtr ptr) noexcept = 0;
  virtual void leftClickOut(EntityPtr ptr) noexcept = 0;
  virtual void RightClickOn(EntityPtr ptr) noexcept = 0;
  virtual void RightClickOut(EntityPtr ptr) noexcept = 0;
  virtual void cursorMoved() noexcept = 0;
  virtual void deselected(EntityPtr ptr) noexcept = 0;
};

#endif /* ENTITYCONTROLLER_H */

