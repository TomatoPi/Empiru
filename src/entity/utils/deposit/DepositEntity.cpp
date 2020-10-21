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
/// \file   DepositEntity.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 20:31
///

#include "DepositEntity.h"

const decorator::Deposit& DepositEntity::deposit() const noexcept {
  return static_cast<const decorator::Deposit&>(*getDecorator<decorator::Deposit>());
}

DepositEntity::Builder::Builder(
  GameEngineInterface& engine, 
  const WorldObject::Position& pos,
  Stack::Ressource type, int qty) 
noexcept :
  Entity::Builder(WorldObject(WorldObject::Size::Small, 0.1, pos)), 
  _engine(engine), 
  _type(type), 
  _qty(qty)
{
}

void DepositEntity::Builder::operator() (Pointer& ptr) const noexcept {
  this->Entity::Builder::operator ()(ptr);
  decorator::Deposit::Builder depbuilder(ptr, _type, _qty, 5);
  _engine.createDecorator(typeid(decorator::Deposit), depbuilder);
}