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
/// \file   GenericSelectorController.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 21:42
///

#ifndef GENERICSELECTORCONTROLLER_H
#define GENERICSELECTORCONTROLLER_H

#include "controller/core/EntityControllerInterface.h"
#include "controller/core/GameControllerInterface.h"

class GenericSelectorController : public EntityControllerInterface {
private:
  GameControllerInterface& _controller;
public:
  GenericSelectorController(GameControllerInterface& c) noexcept : 
    _controller(c) {}

  virtual void leftClickOn(Pointer ptr) noexcept override {
    _controller.selectObject(ptr);
  }
  virtual void leftClickOut(Pointer ptr) noexcept override {
    _controller.deselectObject(_controller.selection());
  }
  virtual void RightClickOn(Pointer ptr) noexcept override {
    /* nothing */
  }
  virtual void RightClickOut(Pointer ptr) noexcept override {
    /* nothing */
  }
  virtual void cursorMoved() noexcept override {
    /* nothing */
  }
  virtual void deselected(Pointer ptr) noexcept override {
    /* nothing */
  }
};

#endif /* GENERICSELECTORCONTROLLER_H */

