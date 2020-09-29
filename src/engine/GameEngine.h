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
/// \file   GameEngine.h
/// \author Alexis CORREIA HENRIQUES <alex2ikangame@gmail.com>
///
/// \date 11 septembre 2020, 16:32
/// \brief Handler of in-game mechanics
///

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "utils/world/WorldInterface.h"
#include "utils/world/WorldRef.h"
#include "utils/engine/Allocator.h"
#include "utils/engine/Behaviourer.h"
#include "utils/engine/Observer.h"
#include "events/GameEvents.h"

#include "entity/functionals/TribeInfos.h"

#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <list>

/// \brief Core object for in-game mechanics
class GameEngine : public Subject, public Observer {
private:

  /// \brief Table of storage by objects type
  typedef std::unordered_map<std::type_index, Allocator*>   ObjectsTable;
  /// \brief Table of behaviours by objects type
  typedef std::unordered_map<std::type_index, Behaviourer*> BehaviourTable;
  /// \brief Store Behaviours in order of their priority
  typedef std::list<std::type_index> PriorityTable;
  /// \brief Store list of objects beeing created
  typedef std::vector<WorldRef*> DyingObjectsList;
  
  ObjectsTable     _objects; ///< Table of all things that do things
  BehaviourTable   _behavs;  ///< Table of behaviours
  PriorityTable    _priors;  ///< List of behaviours ordered on priority
  DyingObjectsList _dyings;  ///< List of objects beeing destroyed
  
  TribeInfos   _playerTribe; ///< Object that store player's tribe infos
  WorldInterface & _world;   ///< THA WO... oh wait ... joke already used
  
  static GameEngine * _Engine;
  
public:
  
  static GameEngine & Get() noexcept {
    return *_Engine;
  }
  
  /// \brief Contructor
  GameEngine(WorldInterface & w);
  
  /// \brief Add an object to the game
  template <typename Builder>
  WorldRef * createObject(const std::type_info & type, const Builder & builder) {
    WorldRef * ref(_objects.at(std::type_index(type))->createObject());
    builder(ref);
    _world.addObject(ref);
    this->sendNotification(EventObjectCreated(ref));
    return ref;
  }
  /// \brief Remove an object from the game
  /// The object is marked for destruction, and removed when we are sure that
  /// it will not break the game
  void removeObject(WorldRef * ref);
  
  /// \brief Add an object kind to the gameEngine
  void registerObjectKind(const std::type_info & type, Allocator * alloc);
  /// \brief Add a behaviour for an object Kind.
  ///   Only kinds with behaviour are sweeped during game tick
  ///   Different types are processed in the same order as their addition
  void attachBehaviour(const std::type_info & type, Behaviourer * behav);
  
  TribeInfos & playerTribe();
  const TribeInfos & playerTribe() const;
  
  /// \brief Called on each Main-loop iteration
  ///   Call behaviour of each object
  void update();
};

#endif /* GAMEENGINE_H */
