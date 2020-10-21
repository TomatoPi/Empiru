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
/// \file   House.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 22 septembre 2020, 09:18
///

#ifndef HOUSE_H
#define HOUSE_H

#include "engine/core/entity/Entity.h"
#include "engine/core/EngineInterface.h"

#include "entity/decorators/storage/Storage.h"

/// \brief The ultimate worker, useful to make anything you can think of
/// \todo revise the path system
class House : public Entity {
public:
  
  const decorator::Storage& storage() const noexcept;
  
  class Builder : public Entity::Builder {
  private:
    
    GameEngineInterface& _engine;
    
  public:
    
    Builder(GameEngineInterface& engine, const WorldObject::Position& pos) noexcept;
    virtual void operator() (Pointer& ptr) const noexcept override;
  };
};

#endif /* HOUSE_H */
