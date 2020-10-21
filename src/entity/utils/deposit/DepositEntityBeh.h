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
/// \file   DepositBeh.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 19:01
///

#ifndef DEPOSITBEH_H
#define DEPOSITBEH_H

#include "entity/decorators/deposit/Deposit.h"
#include "engine/core/entity/EntityBehaviour.h"
#include "engine/core/EngineInterface.h"

class DepositEntityBeh : public EntityBeh {
private:
  
  GameEngineInterface& _engine;
  
public:
  
  explicit DepositEntityBeh(GameEngineInterface& engine) noexcept : 
    _engine(engine) 
  {
  }
  virtual ~DepositEntityBeh() noexcept = default;
  
  virtual void 
  operator() (Entity& entity, Pointer ptr) noexcept override {
    const decorator::Deposit& deposit(static_cast<decorator::Deposit&>(
      *entity.getDecorator<decorator::Deposit>()));
    if (deposit.isEmpty()) {
      _engine.discardEntity(ptr);
    }
  }
};

#endif /* DEPOSITBEH_H */

