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
/// \file   IWorld.h
/// \author tomato
///
/// \date 28 oct. 2020 14:38:41
///
#ifndef SOURCES_GAME_IGENGINE_H_
#define SOURCES_GAME_IGENGINE_H_

#include "EUID.h"
#include "Entity.h"
#include "Decorator.h"
#include <map>

namespace game {

class IGEngine {
public:
  using Entity = std::map<DUID,Decorator::Pointer>; // @suppress("Invalid template argument")
  virtual ~IGEngine() noexcept = default;
  virtual void createEntity(EntityBuilder&) noexcept = 0;
  virtual Entity& getEntity(const EUID uid) noexcept = 0;
};

}  // namespace game

#endif /* SOURCES_GAME_IGENGINE_H_ */
