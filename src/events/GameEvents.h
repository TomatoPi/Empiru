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
/// \file   GameEvents.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 27 septembre 2020, 16:54
///

#ifndef GAMEEVENTS_H
#define GAMEEVENTS_H

#include "utils/world/WorldRef.h"
#include "utils/engine/Observer.h"

struct EventObjectCreated : public Event {
public:
  WorldRef *_obj;
  EventObjectCreated(WorldRef *obj) noexcept : _obj(obj) {}
};

struct EventObjectDestroyed : public Event {
public:
  WorldRef *_obj;
  EventObjectDestroyed(WorldRef *obj) noexcept : _obj(obj) {}
};

#endif /* GAMEEVENTS_H */

