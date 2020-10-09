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

#include "utils/core/IndexAllocator.h"
#include "utils/core/Observer.h"

#include "engine/core/EngineInterface.h"
#include "engine/core/Register.h"
#include "world/core/MapInterface.h"

#include "entity/functionals/TribeInfos.h"

/// \brief Core object for in-game mechanics
class GameEngine : 
  public GameEngineInterface, 
  public Subject, 
  public Observer 
{
private:
  
  typedef Register<Entity,EntityPtr,EntityBeh> EntitiesReg;
  typedef Register<Decorator,DecoratorPtr,DecoratorBeh> DecoratorsReg;
  
  EntitiesReg   _entities;
  DecoratorsReg _decorators;
  TribeInfos    _playerTribe; ///< Object that store player's tribe infos
  MapInterface& _world;       ///< THA WO... oh wait ... joke already used
  
public:
  
  /// \brief Contructor
  GameEngine(MapInterface & w);
  
  TribeInfos & playerTribe();
  const TribeInfos & playerTribe() const;
  
  /// \brief Called on each Main-loop iteration
  ///   Call behaviour of each object
  void update();
  
  
  virtual EntityPtr 
  createEntity(const std::type_info& type, const Entity::Builder& builder) 
  noexcept override;
  
  virtual void 
  discardEntity(EntityPtr ptr) 
  noexcept override;
  
  virtual void 
  registerEntity(const std::type_info& type, EAllocator*, EntityBeh*) 
  noexcept override;
  
  
  virtual DecoratorPtr
  createDecorator(const std::type_info& type, const Decorator::Builder& builder)
  noexcept override;
  
  virtual void 
  dirscardDecorator(DecoratorPtr ptr) 
  noexcept override;
  
  virtual void
  registerDecorator(const std::type_info& type, DAllocator*, DecoratorBeh*) 
  noexcept override;
};

#endif /* GAMEENGINE_H */
