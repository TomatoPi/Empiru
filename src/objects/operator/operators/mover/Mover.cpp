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
/// \file   Mover.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 22 octobre 2020, 21:01
///

#include "Mover.h"

#include "objects/decorator/decorators/worldobj/WorldObject.h"
#include "utils/hex/Consts.h"
#include "utils/log.h"

namespace operators {
  
  using decorators::WorldObject;
  
  void Mover::clear() noexcept {
    _target.clear();
  }
  void Mover::setTarget(const world::Position& target, float tolerance) noexcept {
    clear();
    stackTarget(target);
    _tolerance = tolerance;
  }
  void Mover::stackTarget(const world::Position& target) noexcept {
    _target.emplace_back(target);
    WorldObject& obj(static_cast<WorldObject&>(*_object));
    _dir = (target - obj.pos()).unit();
    obj.orientation(_dir.orientation());
  }
  void Mover::unstackTarget() noexcept {
    _target.pop_back();
    if (!_target.empty()) {
      WorldObject& obj(static_cast<WorldObject&>(*_object));
      _dir = (_target.back() - obj.pos()).unit();
      obj.orientation(_dir.orientation());  
    }
  }

  bool Mover::update() noexcept {
    /* Trivial exit */
    if (_target.empty()) {
      return false;
    }
    /* Check if target is reached */
    WorldObject& obj(static_cast<WorldObject&>(*_object));
    if (world::Position::distance(obj.pos(), _target.back()) < _tolerance) {
      unstackTarget();
      if (_target.empty()) {
        core::OSubject<MoverEvents::TargetReached>::notify();
        return false;
      }
    }
    /* compute a walk step */
    const world::Position oldpos(obj.pos());
    world::Position newpos(oldpos + _dir * _speed);
    core::Pointer obstacle_p(nullptr);
    /* search for an alternative path */
    if (!_worldMap->tryPosition(newpos, _object, &obstacle_p)) {
      if (!obstacle_p) {
        LOG_TODO("Implement dodge Borders\n");
        core::OSubject<MoverEvents::ObstructedPath>::notify();
        return true;
      }
      const WorldObject& obstacle(static_cast<const WorldObject&>(*obstacle_p));
      /* compute the alternatives */
      const world::Position& target(_target.back());
      world::Position collide((newpos - obstacle.pos()).unit());
      world::Position esc1(collide * hex::RMatrix_C60A);
      world::Position esc2(collide * hex::RMatrix_CC60A);
      world::Position& esc = esc1;
      /* get the most direct one */
      if (world::Position::distance(oldpos + esc2 * _speed, target) 
        < world::Position::distance(oldpos + esc1 * _speed, target)) 
      {
        esc = esc2;
      }
      /* stack a circumvention of obstacle */
      newpos = oldpos;
      stackTarget(oldpos + esc * obstacle.radius());
    }
    /* update object's position */
    obj.pos(newpos);
    return true;
  }
}