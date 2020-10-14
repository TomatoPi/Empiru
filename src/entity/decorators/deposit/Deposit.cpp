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
/// \file   Deposit.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 19:02
///

#include "Deposit.h"

namespace deco {
 
  Deposit::Builder::Builder(
    const EntityPtr& entity, 
    Stack::Ressource type, 
    int size, int difficulty)
  noexcept :
    Inventory::Builder(entity),
    _difficulty(difficulty),
    _size(size),
    _type(type)
  {  
  }

  void Deposit::Builder::operator() (DecoratorPtr& ptr) const noexcept {
    this->Inventory::Builder::operator()(ptr);
    Deposit& deposit(static_cast<Deposit&>(*ptr));
    deposit._stack = Stack(_type, _size);
    deposit._difficulty = _difficulty;
  }
}