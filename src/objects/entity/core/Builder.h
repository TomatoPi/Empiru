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
/// \file   Builder.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 23 octobre 2020, 23:48
///

#ifndef ENTITY_BUILDER_H
#define ENTITY_BUILDER_H

#include "core/Builder.h"
#include "Entity.h"
#include "objects/decorator/decorators/worldobj/Builder.h"

namespace Entity {
  class Builder : public core::Builder {
  private:
    
    world::Position _pos;         ///< Object's position
    float           _radius;      ///< Hitbox radius for small objects
    int             _orientation; ///< Object's orientation
    decorators::WorldObject::Size _size; ///< Object's size
    
  public:
    
    Builder(
      const world::Position& p, 
      decorators::WorldObject::Size s, float r=0.5, int o=0)
    noexcept :
      core::Builder(), _pos(p), _radius(r), _orientation(o), _size(s) 
    {
    }
      
    void operator() (core::Pointer& ptr) noexcept override {
      this->core::Builder::operator() (ptr);
      Base& entity(static_cast<Base&>(*ptr));
      decorators::WorldObjectBuilder bld(ptr, _pos, _size, _radius, _orientation);
      entity._position = core::IAllocator::Get().createObject(
        typeid(decorators::WorldObject), bld);
    }
  };
}

#endif /* ENTITY_BUILDER_H */

