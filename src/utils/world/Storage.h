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
/// \file   Storage.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 22 septembre 2020, 09:25
///

#ifndef STORAGE_H
#define STORAGE_H

#include "Ressource.h"
#include <unordered_set>
#include <string>

/// \brief Component for WorldObjects that store ressources
class Storage {
private:
  
  /// \brief Table of Stack hashed by type
  typedef std::unordered_set<Stack, StackTypeHash, StackTypeEqual> StackList;
  StackList _storage; ///< Current storage
  
public:
  
  /// \brief Construct a storage
  Storage() noexcept : 
    _storage()
  {   
  }
  Storage(const Storage &) = default;
  Storage & operator= (const Storage &) = default;
  /// \brief Make class polymorphic
  virtual ~Storage() = default;
  
  /// \brief add given stack to the storage
  void addToStorage(const Stack & stack) noexcept {
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
  
  bool canStore(Stack::Ressource type) const noexcept {
    return true;
  }
  
  /// \brief Debug method
  std::string content_str() const noexcept {
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
};

#endif /* STORAGE_H */
