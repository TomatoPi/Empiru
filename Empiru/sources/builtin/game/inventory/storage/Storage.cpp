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

namespace builtin {
namespace game {
namespace inventory {

items::Stack Storage::doAdd(const items::Stack &stack) noexcept {
  assert(0 < storableQtyOf(stack.type()));
  return _storage[stack.type()].add(stack); // @suppress("Method cannot be resolved")
}
items::Stack Storage::doReduce(items::Ressource type, int qty) noexcept {
  assert(0 < storableQtyOf(type));
  return _storage[type].reduce(qty); // @suppress("Method cannot be resolved")
}

int Storage::storableQtyOf(items::Ressource type) const noexcept {
  if (auto itr = _storage.find(type); itr != _storage.end()) { // @suppress("Method cannot be resolved")
    return itr->second.max() - itr->second.size(); // @suppress("Method cannot be resolved") // @suppress("Field cannot be resolved")
  }
  return 0;
}
bool Storage::isEmpty() const noexcept {
  for (auto [type, stack] : _storage) { // @suppress("Symbol is not resolved")
    if (!stack.empty()) { // @suppress("Method cannot be resolved")
      return false;
    }
  }
  return true;
}

bool Storage::isFull() const noexcept {
  for (auto [type, stack] : _storage) { // @suppress("Symbol is not resolved")
    if (!stack.full()) { // @suppress("Method cannot be resolved")
      return false;
    }
  }
  return true;
}

Storage::Content Storage::content() const noexcept {
  Content res;
  for (auto [type, stack] : _storage) { // @suppress("Symbol is not resolved")
    res.push_back(stack); // @suppress("Invalid arguments")
  }
  return res;
}

void Storage::Builder::operator()(Pointer &ptr) noexcept {
  this->Decorator::Builder::operator()(ptr);
  Storage &store(ptr->as<Storage>());
  for (auto [type, max] : maxes) {
    store._storage.emplace(type, items::Stack(type, 0, max)); // @suppress("Method cannot be resolved")
  }
}

}  // namespace inventory
}  // namespace game
}  // namespace builtin

