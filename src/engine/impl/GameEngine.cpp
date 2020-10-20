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
  BigSubject(), BigObserver(),
  _entities(),
  _decorators()
{
}

/// \brief Called on each Main-loop iteration
///   Call behaviour of each object
void GameEngine::update() {
  /* compute entitites masters behaviours */
  _entities.behave(
      [this](Entity& entity, EntityPtr& ptr, EntityBeh* beh) -> void {
        (*beh)(entity, ptr);
      });
  /* then compute sub-behaviour for each components */
  _decorators.behave(
      [this](decorator::Decorator& dec, decorator::DecoratorPtr& ptr, decorator::Updator* beh) -> void {
        (*beh)(dec, ptr);
      });
  /* destroy entites that died this tick */
  _entities.destroyGarbage(
      [this](EntityPtr ptr) -> void {
        ptr->forEachDecorator(
            [this](decorator::DecoratorPtr& ptr) -> void {
              _decorators.destroyObject(ptr);
            });
      });
  _decorators.destroyGarbage([](const decorator::DecoratorPtr&)->void{});
}


EntityPtr 
GameEngine::createEntity(const std::type_info& type, const Entity::Builder& builder)
noexcept
{
  EntityPtr entity(_entities.createObject(type, builder));
  sendNotification(EventObjectCreated(entity));
  return entity;
}

void 
GameEngine::discardEntity(EntityPtr ptr) 
noexcept
{
  sendNotification(EventObjectDestroyed(ptr));
  _entities.destroyObject(ptr);
}

void 
GameEngine::registerEntity(
  const std::type_info& type, 
  EAllocator* alloc, 
  EntityBeh* beh) 
noexcept
{
  _entities.registerKind(type, alloc);
  if (beh) {
    _entities.registerBehav(type, beh);
  }
}


decorator::DecoratorPtr
GameEngine::createDecorator(const std::type_info& type, const decorator::Decorator::Builder& builder)
noexcept
{
  return _decorators.createObject(type, builder);
}

void 
GameEngine::dirscardDecorator(decorator::DecoratorPtr ptr) 
noexcept
{
  _decorators.destroyObject(ptr);
}

void
GameEngine::registerDecorator(
  const std::type_info& type, 
  DAllocator* alloc, 
  decorator::Updator* beh) 
noexcept
{
  _decorators.registerKind(type, alloc);
  if (beh) {
    _decorators.registerBehav(type, beh);
  }
}