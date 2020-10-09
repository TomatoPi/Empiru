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

#include "utils/core/Allocator.h"
#include "utils/world/core/EntityPtr.h"
#include "utils/world/map/MapInterface.h"
#include "utils/engine/Behaviourer.h"
#include "utils/core/Observer.h"
#include "events/GameEvents.h"

#include "entity/functionals/TribeInfos.h"

#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <list>

/// \brief Core object for in-game mechanics
class GameEngine : public Subject, public Observer {
private:
  
  typedef core::Allocator<WorldObject,WorldPtr,std::size_t> _Allocator;

  /// \brief Table of storage by objects type
  typedef std::unordered_map<std::type_index, _Allocator*>   ObjectsTable;
  /// \brief Table of behaviours by objects type
  typedef std::unordered_map<std::type_index, Behaviourer*> BehaviourTable;
  /// \brief Store Behaviours in order of their priority
  typedef std::list<std::type_index> PriorityTable;
  /// \brief Store list of objects beeing created
  typedef std::vector<WorldPtr> DyingObjectsList;
  
  ObjectsTable     _objects; ///< Table of all things that do things
  BehaviourTable   _behavs;  ///< Table of behaviours
  PriorityTable    _priors;  ///< List of behaviours ordered on priority
  DyingObjectsList _dyings;  ///< List of objects beeing destroyed
  
  TribeInfos   _playerTribe; ///< Object that store player's tribe infos
  MapInterface & _world;   ///< THA WO... oh wait ... joke already used
  
public:
  
  /// \brief Contructor
  GameEngine(MapInterface & w);
  
  /// \brief Add an object to the game
  template <typename Builder>
  WorldPtr createObject(const std::type_info & type, const Builder & builder) {
    WorldPtr ptr(_objects.at(std::type_index(type))->createObject());
    builder(ptr);
    _world.addObject(ptr);
    this->sendNotification(EventObjectCreated(ptr));
    return ptr;
  }
  /// \brief Remove an object from the game
  /// The object is marked for destruction, and removed when we are sure that
  /// it will not break the game
  void removeObject(WorldPtr ptr);
  
  /// \brief Add an object kind to the gameEngine
  void registerObjectKind(const std::type_info & type, _Allocator * alloc);
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
