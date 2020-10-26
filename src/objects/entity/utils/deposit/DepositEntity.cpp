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
#include "objects/decorator/decorators/drawable/Helpers.h"

namespace {
  bool isInventoryType(const std::type_info& type) noexcept {
    return typeid(decorators::Deposit) == type 
        || typeid(decorators::Inventory) == type;
  }
}

core::Pointer 
DepositEntity::doFindDecorator(const std::type_info& type) noexcept {
  if (isInventoryType(type)) 
    return _deposit;
  return core::Pointer(nullptr);
}
const core::Pointer 
DepositEntity::doFindDecorator(const std::type_info& type) const noexcept {
  if (isInventoryType(type)) 
    return _deposit;
  return core::Pointer(nullptr);
}

DepositEntity::Builder::Builder(
      const world::Position& pos,
      Stack::Ressource type, int qty)
noexcept :
  Entity::Builder(pos, decorators::WorldObject::Size::Small, 0.1),
  _type(type), 
  _qty(qty)
{
}

void DepositEntity::Builder::operator() (core::Pointer& ptr) noexcept {
  this->Entity::Builder::operator() (ptr);
  DepositEntity& entity(static_cast<DepositEntity&>(*ptr));
  /* create the corect inventory */
  decorators::Deposit::Builder dbuild(ptr, _type, _qty, 5);
  entity._deposit = core::IAllocator::Get().createObject(
    typeid(decorators::Deposit), dbuild);
  /* suicide the deposit if empty */
  entity._deposit->as<decorators::Inventory>()
    .core::OSubject<decorators::InventoryEvents::Empty>::addSubscriber(
      ptr, core::sudoCommitSuicide<decorators::InventoryEvents::Empty>(ptr));
  
}