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
/// \file   DepositEntity.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 20:02
///

#ifndef DEPOSITENTITY_H
#define DEPOSITENTITY_H

#include "engine/core/entity/Entity.h"
#include "engine/core/EngineInterface.h"

#include "entity/decorators/deposit/Deposit.h"

/// \brief The ultimate worker, useful to make anything you can think of
/// \todo revise the path system
class DepositEntity : public Entity {
public:
  
  const decorator::Deposit& deposit() const noexcept;
  
  class Builder : public Entity::Builder {
  private:
    
    GameEngineInterface& _engine;
    Stack::Ressource     _type;
    int                  _qty;
    
  public:
    
    Builder(
      GameEngineInterface& engine, 
      const WorldObject::Position& pos,
      Stack::Ressource type, int qty) 
    noexcept;
    
    virtual void operator() (EntityPtr& ptr) const noexcept override;
  };
};

#endif /* DEPOSITENTITY_H */

