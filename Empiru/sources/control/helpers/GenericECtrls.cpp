/*
 * Copyright (C) 2020 tomato
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
/// \file   GenericECtrls.cpp
/// \author tomato
///
/// \date 31 oct. 2020 21:32:06
///

#include "GenericECtrls.h"
#include "../IGameCtrl.h"

namespace ctrl {
namespace helpers {

void NullEntityController::leftClickOn(const game::EUID) noexcept {
  /* nothing */
}
void NullEntityController::leftClickOut(const game::EUID uid) noexcept {
  if (uid) {
    ctrl::IGameCtrl::Get().selectObject(uid);
  }
}
void NullEntityController::RightClickOn(const game::EUID) noexcept {
  /* nothing */
}
void NullEntityController::RightClickOut(const game::EUID) noexcept {
  /* nothing */
}
void NullEntityController::cursorMoved() noexcept {
  /* nothing */
}
void NullEntityController::deselected(const game::EUID) noexcept {
  /* nothing */
}


void GenericEntityController::leftClickOn(const game::EUID uid) noexcept {
  ctrl::IGameCtrl::Get().selectObject(uid);
}
void GenericEntityController::leftClickOut(const game::EUID uid) noexcept {
  ctrl::IGameCtrl::Get().deselectObject(ctrl::IGameCtrl::Get().selection());
}
void GenericEntityController::RightClickOn(const game::EUID) noexcept {
  /* nothing */
}
void GenericEntityController::RightClickOut(const game::EUID) noexcept {
  /* nothing */
}
void GenericEntityController::cursorMoved() noexcept {
  /* nothing */
}
void GenericEntityController::deselected(const game::EUID) noexcept {
  /* nothing */
}

}  // namespace helpers
}  // namespace ctrl
