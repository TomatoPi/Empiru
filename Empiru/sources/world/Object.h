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
/// \file   Object.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 27 oct. 2020 00:26:08
///
#ifndef SOURCES_WORLD_OBJECT_H_
#define SOURCES_WORLD_OBJECT_H_

#include "Position.h"
#include "observer/SuperObserver.h"
#include "alloc/Pointer.h"

namespace world {
namespace Events {

struct ObjectMoved {
  Position oldp;
  Position newp;
  ObjectMoved(const Position &o, const Position &n) noexcept :
      oldp(o), newp(n) {
  }
};

struct ObjectRotated {
  int oldr;
  int newr;
  ObjectRotated(int o, int n) noexcept :
      oldr(o), newr(n) {
  }
};

struct ObjectDiscarded {
};

} /* Events */

class Object: public SuperObserver::Subject<Object, Events::ObjectMoved, // @suppress("Invalid template argument")
    Events::ObjectRotated, Events::ObjectDiscarded> {
public:

  using Pointer = alloc::SmartPointer<Object>;
  template<typename EventT>
  using Subject = SuperObserver::Subject<Object,EventT>; // @suppress("Invalid template argument")

  /// \brief Specify object's size on the map
  enum class Size {
    Small,  ///< Objects that coexist on the same tile with circular hitbox
    Tile,   ///< Objects that occupy the whole tile
    Hollow, ///< Utility objects that don't occupy space
  };

private:

  Pointer _this; ///< Object's UID
  Position _pos;    ///< Object's position
  float _radius;    ///< Hitbox radius for smalls objects
  int _orientation; ///< Object's orientation
  Size _size;       ///< Object's size

public:

  Object() noexcept = delete;
  virtual ~Object() noexcept = default;
  Object(const Pointer &ptr) noexcept;

  void build(Size s, const Position &pos, float r = 0.5, int o = 0) noexcept;

  const Pointer& ptr() const noexcept {
    return _this;
  }

  void discard() noexcept {
    Subject<Events::ObjectDiscarded>::notify(); // @suppress("Function cannot be resolved")
  }

  const world::Position& pos() const noexcept {
    return _pos;
  }
  void pos(const Position &pos) noexcept {
    Position old(_pos);
    _pos = pos;
    Subject<Events::ObjectMoved>::notify(old, _pos); // @suppress("Function cannot be resolved")
  }

  int orientation() const noexcept {
    return _orientation;
  }
  void orientation(int o) noexcept {
    int old(_orientation);
    _orientation = o;
    Subject<Events::ObjectRotated>::notify(old, _orientation); // @suppress("Function cannot be resolved")
  }

  /// \brief return object's radius or 1 if tile sized
  float radius() const noexcept {
    return _radius;
  }

  /// \brief Method that return true if this object collide with given object
  ///   considering obj beeing at pos
  bool
  collide(const Object &obj, const Position &pos) const noexcept;

protected:

  /// \brief Collision between two small objects
  static bool smallCollide(const Object &a, const Position &pa, const Object &b,
      const Position &pb) noexcept {
    return Position::distance(pa, pb) < (a._radius + b._radius);
  }
  /// \brief Collision between two tile objects
  static bool tileCollide(const Position &a, const Position &b) noexcept {
    return a.tile() == b.tile();
  }
  /// \brief Collision between a small object and a tile object
  static bool stCollide(const Object &small, const Position &smallpos,
      const Object &tile, const Position &tilepos) noexcept {
    // Easier to understand with a drawing
    return Position(smallpos + (smallpos - tilepos).toUnit() * small._radius).tile()
        == tilepos.tile();
  }
};
} /* world */

#endif /* SOURCES_WORLD_OBJECT_H_ */
