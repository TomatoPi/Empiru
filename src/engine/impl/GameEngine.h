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

#include "utils/alloc/IndexAllocator.h"
#include "utils/pattern/BigObserver.h"

#include "engine/core/EngineInterface.h"
#include "engine/core/Register.h"

#include "engine/core/entity/EntityBehaviour.h"
#include "engine/core/decorator/DecoratorUpdator.h"

/// \brief Core object for in-game mechanics
class GameEngine : 
  public GameEngineInterface, 
  public BigSubject, 
  public BigObserver 
{
private:
  
  typedef alloc::Allocator<Entity,EntityPtr,std::size_t> EAllocator;
  typedef alloc::Allocator<decorator::Decorator,decorator::DecoratorPtr,std::size_t> DAllocator;
  
  typedef Register<Entity,EntityPtr,EntityBeh> EntitiesReg;
  typedef Register<decorator::Decorator,decorator::DecoratorPtr,decorator::Operator> DecoratorsReg;
  
  EntitiesReg   _entities;
  DecoratorsReg _decorators;
  
public:
  
  /// \brief Contructor
  GameEngine() noexcept;
  virtual ~GameEngine() noexcept = default;
  
  /// \brief Called on each Main-loop iteration
  ///   Call behaviour of each object
  void update();
  
  
  virtual EntityPtr 
  createEntity(const std::type_info& type, const Entity::Builder& builder) 
  noexcept override;
  
  virtual void 
  discardEntity(EntityPtr ptr) 
  noexcept override;
  
  void 
  registerEntity(const std::type_info& type, EAllocator*, EntityBeh*) 
  noexcept;
  
  
  virtual decorator::DecoratorPtr
  createDecorator(const std::type_info& type, const decorator::Decorator::Builder& builder)
  noexcept override;
  
  virtual void 
  dirscardDecorator(decorator::DecoratorPtr ptr) 
  noexcept override;
  
  void
  registerDecorator(const std::type_info& type, DAllocator*, decorator::Operator*) 
  noexcept;
};

#endif /* GAMEENGINE_H */
