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
/// \file   ControllerEvents.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 27 septembre 2020, 12:56
///

#ifndef CONTROLLEREVENTS_H
#define CONTROLLEREVENTS_H

#include "core/Event.h"
#include "core/Pointer.h"

namespace ControllerEvents {
  struct ObjectSelected : public Event {
    core::Pointer _ptr;
    ObjectSelected(const core::Pointer& ptr) noexcept : _ptr(ptr) {}
  };

  struct ObjectDeselected : public Event {
    core::Pointer _ptr;
    ObjectDeselected(const core::Pointer& ptr) noexcept : _ptr(ptr) {}
  };

  struct ObjectAction : public Event {
    core::Pointer _obj;
    core::Pointer _target;
    ObjectAction(const core::Pointer& obj, const core::Pointer& target) 
    noexcept : _obj(obj), _target(target) {}
  };
}

#endif /* CONTROLLEREVENTS_H */

