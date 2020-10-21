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
/// \file   WorldObject.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 21 octobre 2020, 12:08
///

#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include "engine/core/decorator/Decorator.h"
#include "world/core/Types.h"

namespace decorator {
  
  class WorldObject : public Decorator {
  public:
    
    /// \brief Specify object's size on the map
    enum class Size {
      Small,  ///< Objects that can coexist on the same tile with circular hitbox
      Tile,   ///< Objects that occupy the whole tile
      Hollow, ///< Utility objects that don't occupy space
    };
    
    enum class Event {
      Moved,
      Rotated
    };
    
    class Observer {
    public:
      virtual void 
      onNotify(const Pointer&, Event, const world::Position&) noexcept = 0;
    };
    
  private:
    
    std::vector<Pointer> _observers;   ///< List of observers
    world::Position           _pos;         ///< Object's position
    float                     _radius;      ///< Hitbox radius for small objects
    int                       _orientation; ///< Object's orientation
    Size                      _size;        ///< Object's size
    
    void notify(Event event, const world::Position& old) noexcept {
      for (auto& observer : _observers) {
        dynamic_cast<Observer&>(*observer).onNotify(event, old);
      }
    }
    
  public:
    
    WorldObject() noexcept = default;
    virtual ~WorldObject() noexcept = default;
    
    const world::Position& pos() const noexcept {return _pos;}
    void pos(const world::Position& pos) noexcept {
      world::Position old(_pos);
      _pos = pos; 
      notify(Event::Moved, old);
    }
    
    int orientation() const noexcept {return _orientation;}
    void orientation(int o) noexcept {
      _orientation = o; 
      notify(Event::Rotated,world::Position());
    }

    /// \brief return object's radius or 1 if tile sized
    float radius() const noexcept {return _radius;}

    /// \brief Method that return true if this object collide with given object
    ///   considering obj beeing at pos
    bool 
    collide(const WorldObject& obj, const world::Position& pos) const noexcept;
    
  protected:
    
    /// \brief Collision between two small objects
    static bool smallCollide(
      const WorldObject& a, const world::Position& pa, 
      const WorldObject& b, const world::Position& pb) 
    noexcept {
      return world::Position::distance(pa, pb) < (a._radius + b._radius);
    }
    /// \brief Collision between two tile objects
    static bool tileCollide(const world::Position& a, const world::Position& b)
    noexcept {
      return a.tile() == b.tile();
    }
    /// \brief Collision between a small object and a tile object
    static bool stCollide(
      const WorldObject &small, const world::Position& smallpos,
      const WorldObject &tile, const world::Position& tilepos)
    noexcept {
      // Easier to understand with a drawing
      return world::Position(
          smallpos + (smallpos - tilepos).toUnit()
            * small._radius).tile() == tilepos.tile();
    }
  };
}

#endif /* WORLDOBJECT_H */