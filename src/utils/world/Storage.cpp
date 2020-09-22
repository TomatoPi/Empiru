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
/// \date 22 septembre 2020, 09:25
///

#include "Storage.h"
#include "utils/gui/view/AbstractCamera.h"
  
/// \brief Construct a storage
Storage::Storage() : _storage() {
  
}

/// \brief add given stack to the storage
void Storage::addToStorage(const Stack & stack) {
  StackList::iterator itr(_storage.find(stack));
  if (itr == _storage.end()) {
    _storage.emplace_hint(itr, stack);
  } else {
    Stack old(*itr);
    old.reduce(-stack.size());
    _storage.erase(itr);
    _storage.emplace(old);
  }
}

std::string Storage::content_str() const {
  std::string res;
  for (auto & stack : _storage) {
    res.append("[");
    res.append(std::to_string(stack.type()));
    res.append(":");
    res.append(std::to_string(stack.size()));
    res.append("]");
  }
  return res;
}