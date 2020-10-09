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
/// \file   Register.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 03:07
///

#ifndef REGISTER_H
#define REGISTER_H

#include "utils/alloc/IndexPtr.h"
#include "utils/alloc/IndexAllocator.h"

#include <cassert>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <vector>

template <class Base, class Ptr, class Behav>
class Register {
private:
    
  typedef alloc::Allocator<Base,Ptr,std::size_t> Allocator;
  /// \brief Table of storage by objects type
  typedef std::unordered_map<std::type_index, Allocator*> ObjectsTable;
  /// \brief Table of behaviours by objects type
  typedef std::unordered_map<std::type_index, Behav*> BehTable;
  /// \brief Store list of objects beeing created
  typedef std::vector<Ptr> DyingEntitiesList;
  
  ObjectsTable      _objects;     ///< Table of all things that do things
  BehTable          _behaviours;  ///< Table of behaviours
  DyingEntitiesList _dyings;      ///< List of objects beeing destroyed
  
public:
  
  Ptr createObject(const std::type_info& type, const typename Base::Builder& builder) 
  noexcept {
    Ptr ptr(_objects.at(std::type_index(type))->createObject());
    builder(ptr);
    return ptr;
  }
  
  void destroyObject(Ptr ptr) noexcept {
    _dyings.push_back(ptr);
  }
  
  void registerKind(const std::type_info& type, Allocator* alloc) noexcept {
    assert(alloc);
    auto res(_objects.emplace(std::type_index(type), alloc));
    assert(res.second);
  }
  
  void registerBehav(const std::type_info& type, Behav* beh) noexcept {
    assert(beh);
    auto res(_behaviours.emplace(std::type_index(type), beh));
    assert(res.second);
  }
  
  template <class Callback>
  void behave(const Callback& callback) noexcept {
    for (auto& beh : _behaviours) {
      _objects.at(beh.first)->foreach(
        [&](Base& obj, Ptr ptr) -> void {
          callback(obj, ptr, beh.second);
        });
    }
  }
  
  template <class Callback>
  void destroyGarbage(const Callback& callback) noexcept {
    for (auto& ptr : _dyings) {
      callback(ptr);
      _objects.at(std::type_index(typeid(*ptr)))->deleteObject(ptr);
    }
    _dyings.clear();
  }
};

#endif /* REGISTER_H */

