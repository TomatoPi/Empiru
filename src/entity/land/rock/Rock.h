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
/// \file   Rock.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 19 septembre 2020, 14:18
///

#ifndef ROCK_H
#define ROCK_H

#include "entity/utils/deposit/DepositEntity.h"

/// \brief Trees are beautiful things which don't do special things at this moment
class Rock : public DepositEntity {
public:
  
  class Builder : public DepositEntity::Builder {
    public:
      Builder(GameEngineInterface& engine, const WorldObject::Position& pos)
      noexcept : 
        DepositEntity::Builder(engine, pos, Stack::Ressource::Rock, 50)
      {
      }
        
      virtual void operator() (EntityPtr& ptr) const noexcept override {
        this->DepositEntity::Builder::operator ()(ptr);
      }
  };
};
#endif /* ROCK_H */