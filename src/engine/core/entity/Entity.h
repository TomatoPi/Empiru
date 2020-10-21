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

#include "EntityPtr.h"
#include "engine/core/decorator/Pointer.h"
#include <typeinfo>

/// \brief Base class used to represent objects in the world (and a bit more)
class Entity {  
protected:
  
  EntityPtr _this; ///< Sometimes very useful
  
public:
  
  Entity() noexcept = default;
  virtual ~Entity() noexcept = default;
  
  /// \brief Must return a pointer to given decorator if such exist
  ///   nullptr otherwise
  virtual decorator::Pointer 
  findDecorator(const std::type_info& type) noexcept = 0;
  
  /// \brief Must return given decorator, undefined behaviour if none
  virtual decorator::Decorator& 
  getDecorator(const std::type_info& type) noexcept = 0;
  /// \brief Must return given decorator, undefined behaviour if none
  virtual const decorator::Decorator& 
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
  class Builder {
  public:
    Builder() noexcept = default;
    virtual void operator() (EntityPtr& ptr) const noexcept {
      ptr->_this = ptr;
    }
  };
};

#endif /* ENTITY_H */

