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

#include "engine/core/Object.h"
#include "engine/core/IGameAllocator.h"
#include "objects/decorator/core/Decorator.h"
#include "objects/decorator/decorators/worldobj/WorldObject.h"
#include <typeinfo>

/// \brief Base class used to represent objects in the world (and a bit more)
class Entity : public core::Object {
protected:
  
  core::Pointer _pos;
  
public:

  Entity() noexcept = default;
  virtual ~Entity() noexcept = default;

  /// \brief Must return a pointer to given decorator if such exist
  ///   nullptr otherwise
  virtual core::Pointer 
  findDecorator(const std::type_info& type) noexcept = 0;

  /// \brief Must return given decorator, undefined behaviour if none
  virtual Decorator& 
  getDecorator(const std::type_info& type) noexcept = 0;
  /// \brief Must return given decorator, undefined behaviour if none
  virtual const Decorator& 
  getDecorator(const std::type_info& type) const noexcept = 0;

  /// \brief Useful to get and cast a decorator to a subtype
  template <class T>
  T& get() noexcept {
    return static_cast<T&>(getDecorator(typeid(T)));
  }
  /// \brief Useful to get and cast a decorator to a subtype
  template <class T>
  const T& get() const noexcept {
    return static_cast<const T&>(getDecorator(typeid(T)));
  }

  /// \brief The builder of an entity
  class Builder : public core::Object::Builder {
  private:
    IGameAllocator&       _allocator;
    WorldObject::Builder  _posbuilder;
  public:
    Builder(IGameAllocator& a, const WorldObject::Builder& b) noexcept :
      core::Object::Builder(), _allocator(a), _posbuilder(b) {}
    virtual void operator() (core::Pointer& ptr) const noexcept override {
      this->core::Object::Builder::operator() (ptr);
      Entity& entity(static_cast<Entity&>(*ptr));
      _posbuilder._entity = ptr;
      entity._pos = _allocator.createObject(typeid(WorldObject), _posbuilder);
      
    }
  };
}; 

template <>
WorldObject& Entity::get() noexcept {
  return static_cast<WorldObject&>(*_pos);
}
template <>
const WorldObject& Entity::get() const noexcept {
  return static_cast<const WorldObject&>(*_pos);
}

#endif /* ENTITY_H */

