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
/// \file   House.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 22 septembre 2020, 09:18
///

#include "House.h"

const deco::Storage& House::storage() const noexcept {
  return static_cast<const deco::Storage&>(*getDecorator<deco::Storage>());
}

House::Builder::Builder(
  GameEngineInterface& engine, 
  const WorldObject::Position& pos) 
noexcept :
  Entity::Builder(WorldObject(WorldObject::Size::Tile, 0.5, pos)), _engine(engine)
{
}

void House::Builder::operator() (EntityPtr& ptr) const noexcept {
  this->Entity::Builder::operator() (ptr);
  deco::Storage::Builder builder(ptr, {
    Stack(Stack::Ressource::Wood, 0, 100),
    Stack(Stack::Ressource::Rock, 0, 50)
  });
  _engine.createDecorator(typeid(deco::Storage), builder);
}