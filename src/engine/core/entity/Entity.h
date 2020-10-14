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

#include "EntityPtr.h"
#include "engine/core/decorator/DecoratorPtr.h"
#include "world/core/WorldObject.h"

class Entity {  
private:
  
  typedef std::unordered_map<std::type_index,deco::DecoratorPtr> DecoratorsTable;
  DecoratorsTable _decorators;
  
protected:
  
  WorldObject _position;
  
public:
  
  Entity() noexcept : _decorators(), _position() {};
  virtual ~Entity() noexcept = default;
  
  WorldObject& pos() noexcept {
    return _position;
  }
  const WorldObject& pos() const noexcept {
    return _position;
  }
  
  void attachDecorator(const std::type_info& type, const deco::DecoratorPtr& ptr) noexcept {
    bool success(_decorators.emplace(std::type_index(type), ptr).second);
    assert(success && "Duplicated Decorators kind");
  }
  
  void detachDecorator(const std::type_info& type) noexcept {
    auto itr(_decorators.find(std::type_index(type)));
    assert(itr != _decorators.end());
    _decorators.erase(itr);
  }
  
  template <class T>
  deco::DecoratorPtr getDecorator() noexcept {
    DecoratorsTable::iterator 
    itr(_decorators.find(std::type_index(typeid(T))));
    if (itr == _decorators.end()) {
      return deco::DecoratorPtr(nullptr);
    }
    return itr->second;
  }
  
  template <class T>
  const deco::DecoratorPtr getDecorator() const noexcept {
    DecoratorsTable::const_iterator 
    itr(_decorators.find(std::type_index(typeid(T))));
    if (itr == _decorators.end()) {
      return deco::DecoratorPtr(nullptr);
    }
    return itr->second;
  }
  
  template <typename Func>
  void forEachDecorator(const Func& callback) noexcept {
    for (auto& dec : _decorators) {
      callback(dec.second);
    }
  }
  
  class Builder {
  private:
  
    WorldObject _obj;
    
  public:
    
    Builder(const WorldObject& obj) noexcept : _obj(obj) {}
    
    virtual void operator() (EntityPtr& ptr) const noexcept {
      ptr->_position = _obj;
    }
  };
};

#endif /* ENTITY_H */

