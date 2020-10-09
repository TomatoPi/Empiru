/*
 * Copyright (C) 2020 DAGO Kokri Esaïe <dago.esaie@protonmail.com>
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
/// \file   EngineInterface.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 02:11
///

#ifndef ENGINEINTERFACE_H
#define ENGINEINTERFACE_H

#include <typeinfo>
#include "utils/engine/core/entity/EntityPtr.h"
#include "utils/engine/core/entity/Entity.h"
#include "utils/engine/core/decorator/DecoratorPtr.h"
#include "utils/engine/core/decorator/Decorator.h"

class GameEngineInterface {
public:
  
  virtual EntityPtr 
  createEntity(const std::type_info& type, const Entity::Builder& builder) 
  noexcept = 0;
  virtual void discardEntity(EntityPtr ptr) noexcept = 0;
  
  virtual DecoratorPtr
  createDecorator(const std::type_info& type, const Decorator::Builder& builder)
  noexcept = 0;
  virtual void dirscardDecorator(DecoratorPtr ptr) noexcept = 0;
};

#endif /* ENGINEINTERFACE_H */

