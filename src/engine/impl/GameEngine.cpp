/*
 * Copyright (C) 2020 Alexis
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
/// \file   GameEngine.cpp
/// \author Alexis CORREIA HENRIQUES <alex2ikangame@gmail.com>
///
/// \date 11 septembre 2020, 16:32
/// \brief Handler of in-game mechanics
///

#include <cassert>

#include "GameEngine.h"
#include "utils/hex/Consts.h"
#include "engine/events/GameEvents.h"

/// \brief Contructor
GameEngine::GameEngine() noexcept : 
  core::Subject(), 
  core::Observer(),
  _objects(),
  _callables(),
  _dyings()
{
}

/// \brief Called on each Main-loop iteration
///   Call behaviour of each object
void GameEngine::update() {
  /* compute entitites masters behaviours */
  for (auto& type : _callables) {
    _objects.at(type)->foreach(
      [this](core::Object& obj) -> void {
        obj();
      });
  }
  for (auto& ptr : _dyings) {
    _objects.at(std::type_index(typeid(*ptr)))->deleteObject(ptr);
  }
}


core::Pointer 
GameEngine::createObject(
  const std::type_info& type, 
  const core::Object::Builder& builder)
noexcept
{
  core::Pointer object(_objects.at(std::type_index(type))->createObject());
  builder(object);
  sendNotification(GameEvents::ObjectCreated(object));
  return object;
}

void GameEngine::discardObject(core::Pointer ptr) noexcept {
  sendNotification(GameEvents::ObjectDestroyed(ptr));
  _dyings.push_back(ptr);
}

void 
GameEngine::registerObject(
  const std::type_info& type, 
  Allocator* alloc, 
  bool callable) 
noexcept
{
  assert(alloc);
  auto res(_objects.emplace(std::type_index(type), alloc));
  assert(res.second);
  if (callable) {
    _callables.push_back(std::type_index(type));
  }
}