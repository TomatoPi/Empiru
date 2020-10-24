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
/// \date 23 octobre 2020, 23:59
///

#ifndef WORLD_OBJECT_BUILDER_H
#define WORLD_OBJECT_BUILDER_H

#include "objects/decorator/Builder.h"
#include "WorldObject.h"

namespace decorators {
  /// \brief Build a beautiful worldObject
  class WorldObjectBuilder : public Decorator::Builder {
  private:
    
    core::Pointer   _entity;
    world::Position _pos;         ///< Object's position
    float           _radius;      ///< Hitbox radius for small objects
    int             _orientation; ///< Object's orientation
    WorldObject::Size _size;      ///< Object's size
    
  public:
    
    WorldObjectBuilder(
            const core::Pointer& entity, 
            const world::Position& p, 
            WorldObject::Size s, float r=0.5, int o=0)
    noexcept :
      Decorator::Builder(entity),
      _entity(entity), _pos(p), _radius(r), _orientation(o), _size(s) 
    {}
      
    void operator() (core::Pointer& ptr) noexcept override;
  };
}

#endif /* WORLD_OBJECT_BUILDER_H */

