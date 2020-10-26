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

#include "core/Object.h"
#include "core/IAllocator.h"
#include "objects/decorator/decorators/worldobj/WorldObject.h"
#include "objects/decorator/decorators/drawable/Drawable.h"
#include <typeinfo>

namespace Entity {
  class Base : public core::Object {
  protected :
    friend class Builder;
    core::Pointer _position;
    core::Pointer _drawable;
  public:

    Base() noexcept = default;
    virtual ~Base() noexcept = default;

    /// \brief By default entities are not callables
    bool update() noexcept override {assert(0);}

    /// \brief Must return a pointer to given decorator if such exist
    ///   nullptr otherwise
    core::Pointer findDecorator(const std::type_info& type) noexcept {
      if (type == typeid(decorators::WorldObject)) {
        return _position;
      } 
      else if (type == typeid(decorators::Drawable)) {
        return _drawable;
      }
      else {
        return doFindDecorator(type);
      }
    }
    /// \brief Must return a pointer to given decorator if such exist
    ///   nullptr otherwise
    const core::Pointer findDecorator(const std::type_info& type) const noexcept {
      if (type == typeid(decorators::WorldObject)) {
        return _position;
      } 
      else if (type == typeid(decorators::Drawable)) {
        return _drawable;
      }
      else {
        return doFindDecorator(type);
      }
    }

    /// \brief Useful to get and cast a decorator to a subtype
    template <class T>
    T& get() noexcept {
      return static_cast<T&>(*findDecorator(typeid(T)));
    }
    /// \brief Useful to get and cast a decorator to a subtype
    template <class T>
    const T& get() const noexcept {
      return static_cast<const T&>(*findDecorator(typeid(T)));
    }

  protected:
    
    /// \brief Must return a pointer to given decorator if such exist
    ///   nullptr otherwise
    virtual core::Pointer 
    doFindDecorator(const std::type_info& type) noexcept = 0;
    /// \brief Must return a pointer to given decorator if such exist
    ///   nullptr otherwise
    virtual const core::Pointer 
    doFindDecorator(const std::type_info& type) const noexcept = 0;
  };
  
  template <>
  decorators::WorldObject& Base::get() noexcept {
    return static_cast<decorators::WorldObject&>(*_position);
  }
  template <>
  const decorators::WorldObject& Base::get() const noexcept {
    return static_cast<const decorators::WorldObject&>(*_position);
  }
  
  template <>
  decorators::Drawable& Base::get() noexcept {
    return static_cast<decorators::Drawable&>(*_drawable);
  }
  template <>
  const decorators::Drawable& Base::get() const noexcept {
    return static_cast<const decorators::Drawable&>(*_drawable);
  }
}

#endif /* ENTITY_H */

