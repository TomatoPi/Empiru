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
#include "utils/log.h"
#include "PeonEntity.h"
#include "objects/operator/operators/mover/Mover.h"

namespace peon {
  void PeonController::leftClickOn(core::Pointer ptr) noexcept {
    if (_controller.selection() != ptr) {
      _controller.selectObject(ptr);
      static_cast<PEntity&>(*ptr).get<PeonSprite>()._select = true;
    }
  }
  void PeonController::leftClickOut(core::Pointer ptr) noexcept {
    _controller.deselectObject(_controller.selection());
    static_cast<PEntity&> (*ptr).get<PeonSprite>()._select = false;
  }
  void PeonController::RightClickOn(core::Pointer ptr) noexcept {
    /* nth */
  }
  void PeonController::RightClickOut(core::Pointer ptr) noexcept {
    core::Pointer pptr(_controller.selection());
    if (!ptr) {
      /* first */
      PEntity& peon(static_cast<PEntity&>(*ptr));
      if (!peon._mover) {
        Mover::Builder mBuilder(&_worldmap, peon._pos, 0.01f);
        peon._mover = _allocator.createObject(typeid(Mover), mBuilder);
        peon.subscribe(peon._mover);
      }
      Mover& mover(peon.get<Mover>());
      mover.clear();
      mover.setTarget(_controller.cursor(), 0.01);
      _controller.objectAction(pptr, core::Pointer(nullptr));
    } else {
      /*
      Peon& peon(static_cast<Peon&>(*pptr));
      if (decorators::Pointer dptr = ptr->getDecorator<decorators::Deposit>()) {
        decorators::Deposit& deposit(static_cast<decorators::Deposit&>(*dptr));
        if (!deposit.isEmpty()) {
          if (0 < peon.inventory().storableQtyOf(deposit.content().front().type())) {
            peon.collector().collectAt(dptr, deposit.content().front().type());
          } 
        }
      }
      else if (decorators::Pointer sptr = ptr->getDecorator<decorators::Storage>()) {
        decorators::Storage& store(static_cast<decorators::Storage&>(*sptr));
        if (!peon.inventory().isEmpty()) {
          if (0 < store.storableQtyOf(peon.inventory().content().front().type())) {
            peon.collector().storeAt(sptr, peon.inventory().content().front().type());
          }
        }
      }
       */
    }
  }
  void PeonController::cursorMoved() noexcept {
    /* nth */
  }
  void PeonController::deselected(core::Pointer ptr) noexcept {
    /* nth */
  }
}