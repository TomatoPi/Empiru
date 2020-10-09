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
/// \file   Storage.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 22:22
///

#include "Storage.h"

Stack StorageDecorator::addToStorage(const Stack & stack) noexcept {
  StackList::iterator itr(_storage.find(stack));
  if (itr == _storage.end()) {
    _storage.emplace_hint(itr, stack);
  } else {
    Stack old(*itr);
    old.reduce(-stack.size());
    _storage.erase(itr);
    _storage.emplace(old);
  }
  return Stack();
}

    
StorageDecorator::Builder::Builder(const EntityPtr& entity) noexcept :
  Decorator::Builder(entity)
{  
}
void StorageDecorator::Builder::operator() (DecoratorPtr& ptr) const noexcept {
  this->Decorator::Builder::operator() (ptr);
}