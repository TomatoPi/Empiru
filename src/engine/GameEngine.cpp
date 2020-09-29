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

/// \brief Contructor
GameEngine::GameEngine(WorldInterface & w) : 
  _objects(),
  _behavs(),
  _priors(),
  _world(w)
{
  
}

/// \brief Remove an object from the game
void GameEngine::removeObject(WorldRef * ref) {
  this->sendNotification(EventObjectDestroyed(ref));
  _world.removeObject(ref);
  _objects.at(std::type_index(typeid(**ref)))->deleteObject(ref);
}

/// \brief Add an object kind to the gameEngine
void GameEngine::registerObjectKind(const std::type_info & type, Allocator * alloc) {
  auto res(_objects.emplace(std::type_index(type), alloc));
  assert(res.second);
}
/// \brief Add a behaviour for an object Kind.
///   Only kinds with behaviour are sweeped during game tick
void GameEngine::attachBehaviour(const std::type_info & type, Behaviourer * behav) {
  auto res(_behavs.emplace(std::type_index(type), behav));
  _priors.emplace_back(std::type_index(type));
  assert(res.second);
}

TribeInfos & GameEngine::playerTribe() {
  return _playerTribe;
}
const TribeInfos & GameEngine::playerTribe() const {
  return _playerTribe;
}

/// \brief Called on each Main-loop iteration
///   Call behaviour of each object
void GameEngine::update() {
  /* first init the tribe */
  _playerTribe.init();
  for (auto & type : _priors) {
    auto & beh(_behavs.at(type));
    auto & alloc(_objects.at(type));
    alloc->foreach(
        [&]
        (WorldObject & obj, WorldRef *ref) -> void {
          beh->tick(obj, ref, _world);
        });
  }
}