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
/// \file   Entity.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 00:20
///

#ifndef ENTITY_H
#define ENTITY_H

#include <cassert>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

#include "utils/engine/core/entity/EntityPtr.h"
#include "utils/engine/core/decorator/DecoratorPtr.h"
#include "utils/world/core/WorldObject.h"

class Entity {  
private:
  
  typedef std::unordered_map<std::type_index,DecoratorPtr> DecoratorsTable;
  DecoratorsTable _decorators;
  
protected:
  
  WorldObject _position;
  
public:
  
  Entity() noexcept : _decorators(), _position() {};
  virtual ~Entity() noexcept = default;
  
  WorldObject& position() noexcept {
    return _position;
  }
  const WorldObject& position() const noexcept {
    return _position;
  }
  
  void attachDecorator(const std::type_info& type, const DecoratorPtr& ptr) noexcept {
    bool success(_decorators.emplace(std::type_index(type), ptr).second);
    assert(success && "Duplicated Decorators kind");
  }
  
  void detachDecorator(const std::type_info& type) noexcept {
    auto itr(_decorators.find(std::type_index(type)));
    assert(itr != _decorators.end());
    _decorators.erase(itr);
  }
  
  template <class T>
  DecoratorPtr getDecorator() noexcept {
    DecoratorsTable::iterator 
    itr(_decorators.find(std::type_index(typeid(T))));
    if (itr == _decorators.end()) {
      return DecoratorPtr(nullptr);
    }
    return itr->second;
  }
  
  template <class T>
  const DecoratorPtr getDecorator() const noexcept {
    DecoratorsTable::const_iterator 
    itr(_decorators.find(std::type_index(typeid(T))));
    if (itr == _decorators.end()) {
      return DecoratorPtr(nullptr);
    }
    return itr->second;
  }
  
  template <typename Func>
  void forEachDecorator(const Func& callback) noexcept {
    for (auto& dec : _decorators) {
      callback(dec);
    }
  }
  
  class Builder {
  private:
  
    WorldObject _obj;
    
    Builder(const WorldObject& obj) noexcept : _obj(obj) {}
    
    void operator() (EntityPtr& ptr) const noexcept {
      ptr->_position = _obj;
    }
  };
};

#endif /* ENTITY_H */

