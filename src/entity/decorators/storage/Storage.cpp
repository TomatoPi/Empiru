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

#include <vector>

#include "Storage.h"

namespace decorator {
  
  Stack Storage::doAdd(const Stack& stack) noexcept {
    assert(storableQtyOf(stack.type()));
    return _storage[static_cast<std::size_t>(stack.type())].add(stack);
  }
  Stack Storage::doReduce(Stack::Ressource type, int qty) noexcept {
    assert(storableQtyOf(type));
    return _storage[static_cast<std::size_t>(type)].reduce(qty);
  }

  int Storage::storableQtyOf(Stack::Ressource type) const noexcept {
    const Stack& stack(_storage[static_cast<std::size_t>(type)]);
    return stack.max() - stack.size();
  }
  bool Storage::isEmpty() const noexcept {
    for (const auto& stack : _storage) {
      if (!stack.empty()) {
        return false;
      }
    }
    return true;
  }
  
  bool Storage::isFull() const noexcept {
    for (const auto& s : _storage) {
      if (!s.full()) {
        return false;
      }
    }
    return true;
  }

  Storage::Content Storage::content() const noexcept {
    Content res;
    for (const auto& stack : _storage) {
      if (0 < stack.max()) {
        res.push_back(stack);
      }
    }
    return res;
  }

  Storage::Builder::Builder(
        const EntityPtr& entity, 
        const std::initializer_list<Stack>& maximums) 
  noexcept :
    Inventory::Builder(entity),
    _maximums()
  {  
    for (const auto& stack : maximums) {
      std::size_t idx(static_cast<std::size_t>(stack.type()));
      _maximums[idx] = Stack(stack.type(), 0, stack.max());
    }
  }
  void Storage::Builder::operator() (Pointer& ptr) const noexcept {
    this->Inventory::Builder::operator() (ptr);
    Storage& store(static_cast<Storage&>(*ptr));
    store._storage = _maximums;
  }

}