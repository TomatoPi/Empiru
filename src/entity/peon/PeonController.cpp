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
/// \file   PeonController.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 07:47
///

#include "PeonController.h"
#include "entity/decorators/mover/Mover.h"
#include "utils/log.h"
#include "entity/decorators/deposit/Deposit.h"
#include "PeonEntity.h"

void PeonController::leftClickOn(EntityPtr ptr) noexcept {
  if (_controller.selection() != ptr) {
    _controller.selectObject(ptr);
  }
}
void PeonController::leftClickOut(EntityPtr ptr) noexcept {
  _controller.deselectObject(_controller.selection());
}
void PeonController::RightClickOn(EntityPtr ptr) noexcept {
  /* nth */
}
void PeonController::RightClickOut(EntityPtr ptr) noexcept {
  EntityPtr pptr(_controller.selection());
  if (!ptr) {
    deco::Mover& mover(static_cast<deco::Mover&>(*pptr->getDecorator<deco::Mover>()));
    mover.clearPath();
    mover.setTarget(_controller.cursor(), 0.01);
    _controller.objectAction(pptr, EntityPtr(nullptr));
  } else {
    Peon& peon(static_cast<Peon&>(*pptr));
    if (deco::DecoratorPtr dptr = ptr->getDecorator<deco::Deposit>()) {
      deco::Deposit& deposit(static_cast<deco::Deposit&>(*dptr));
      if (!deposit.content().empty()) {
        if (0 < peon.inventory().storableQtyOf(deposit.content().front().type())) {
          peon.collector().collectAt(dptr, deposit.content().front().type());
        } 
      }
    }
  }
}
void PeonController::cursorMoved() noexcept {
  /* nth */
}
void PeonController::deselected(EntityPtr ptr) noexcept {
  /* nth */
}