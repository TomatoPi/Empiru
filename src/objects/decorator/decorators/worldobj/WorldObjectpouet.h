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
/// \date 16 septembre 2020, 10:51
///

#ifndef WORLD_WORLDOBJECT_H
#define WORLD_WORLDOBJECT_H

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

  private:

    Position _pos;          ///< Object's position
    float    _radius;       ///< Hitbox radius for small objects
    int      _orientation;  ///< Object's orientation
    Size     _size;         ///< Object's size

  public:

    /// \brief Construct an object
    explicit WorldObject(Size s, float r=0.5f, Position p=Position(), int ori=0)
      noexcept;

    /// \brief Default constructor
    WorldObject() noexcept = default;
    /// \brief Copy constructor
    WorldObject(const WorldObject &) noexcept = default;
    /// \brief Copy assignement
    WorldObject& operator= (const WorldObject &) noexcept = default;
    /// \brief Destructor
    ~WorldObject() noexcept = default;

    /// \brief change object's size class
    inline void setSizeClass(Size s) {_size = s;}
    /// \brief return object's size class
    inline Size sizeClass() const noexcept {return _size;}

    /// \brief return object's position
    const Position & pos() const noexcept {return _pos;}
    /// \brief set object's position
    void pos(const Position & pos) noexcept {_pos = pos;}

    int orientation() const noexcept {return _orientation;}
    void orientation(int o) noexcept {_orientation = o;}

    /// \brief return object's radius or 1 if tile sized
    float radius() const noexcept {return _radius;}

    /// \brief Method that must return true obj collides this object
    bool collide(const WorldObject & obj) const noexcept;
    /// \brief Method that return true if pos is in this object
    bool collide(const Position & pos) const noexcept;

    /// \brief Collision between two small objects
    static bool smallCollide(const WorldObject &a, const WorldObject &b) 
      noexcept
    {
      return Position::distance(a._pos, b._pos) < (a._radius + b._radius);
    }
    /// \brief Collision between two tile objects
    static bool tileCollide(const WorldObject &a, const WorldObject &b)
      noexcept
    {
      return a._pos.tile() == b._pos.tile();
    }
    /// \brief Collision between a small object and a tile object
    static bool stCollide(const WorldObject &small, const WorldObject &tile)
      noexcept
    {
      // Easier to understand with a drawing
      return Position(
          small._pos + (small._pos - tile._pos).toUnit() 
            * small._radius).tile() == tile._pos.tile();
    }
  };
}

#endif /* WORLD_WORLDOBJECT_H */