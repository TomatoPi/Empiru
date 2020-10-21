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
/// \file   Decorator.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 8 octobre 2020, 23:13
///

#ifndef DECORATOR_H
#define DECORATOR_H

#include "Pointer.h"
#include "engine/core/entity/EntityPtr.h"
#include "engine/core/entity/Entity.h"
#include <vector>

/// \brief namespace containing all decorator related stuff
namespace decorator {

  class Decorator {
  protected:

    Pointer _this;
    EntityPtr    _entity;

  public:

    Decorator() noexcept : _entity(nullptr) {}
    virtual ~Decorator() noexcept = default;
    
    const EntityPtr& entity() const noexcept {return _entity;}
    
    class Builder {
    private:

      EntityPtr _entity;
      
    protected:
      
      void addMarkers(Pointer& ptr) const noexcept {}
      
      template <typename T, typename ...Ts>
      void addMarkers(Pointer& ptr, const T& type, const Ts& ...types) 
      const noexcept {
        ptr->_entity->attachDecorator(type, ptr);
        addMarkers(ptr, types...);
      }

    public:

      explicit Builder(const EntityPtr& entity) noexcept : 
        _entity(entity) {}

      virtual void operator() (Pointer& ptr) const noexcept {
        ptr->_this = ptr;
        ptr->_entity = _entity;
        ptr->_entity->attachDecorator(typeid(*ptr), ptr);
      }
    };
  };
}

#endif /* DECORATOR_H */

