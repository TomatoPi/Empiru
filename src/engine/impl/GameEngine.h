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

#include "core/Observer.h"
#include "core/IGameAllocator.h"
#include "utils/alloc/impl/IndexAllocator.h"

#include <cassert>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <vector>

/// \brief Core object for in-game mechanics
class GameEngine : 
  public IGameAllocator, 
  public core::Subject,
  public core::Observer
{
private:
  
  /// \brief Typedef for GameAllocators
  typedef alloc::IAllocator<core::Object,core::Pointer> Allocator;
  /// \brief Table of storage by objects type
  typedef std::unordered_map<std::type_index, Allocator*> ObjectsTable;
  /// \brief List of callable types
  typedef std::vector<std::type_index> CallablesList;
  /// \brief Store list of objects beeing created
  typedef std::vector<core::Pointer> DyingEntitiesList;
  
  ObjectsTable      _objects;
  CallablesList     _callables;
  DyingEntitiesList _dyings;
  
public:
  
  /// \brief Contructor
  GameEngine() noexcept;
  virtual ~GameEngine() noexcept = default;
  
  /// \brief Called on each Main-loop iteration
  ///   Call behaviour of each object
  void update();
  
  /// \brief Called to create a new object
  virtual core::Pointer 
  createObject(const std::type_info&, core::Object::Builder&) 
  noexcept override;
  
  /// \brief Called to destroy an object
  virtual void discardObject(core::Pointer ptr) noexcept override;
  
  /// \brief Called to register a new object type
  void 
  registerObject(const std::type_info& type, Allocator* alloc, bool callable=false) 
  noexcept;
};

#endif /* GAMEENGINE_H */
