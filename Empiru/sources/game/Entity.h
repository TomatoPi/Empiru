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
/// \file   Entity.h
/// \author tomato
///
/// \date 28 oct. 2020 15:37:30
///
#ifndef SOURCES_GAME_ENTITY_H_
#define SOURCES_GAME_ENTITY_H_

#include "EUID.h"

namespace game {

struct EntityBuilder {
  virtual ~EntityBuilder() noexcept = default;
  virtual void operator()(const EUID uid) noexcept = 0;
};

}  // namespace game

#endif /* SOURCES_GAME_ENTITY_H_ */