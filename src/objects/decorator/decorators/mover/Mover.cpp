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
/// \date 9 octobre 2020, 08:34
///

#include "Mover.h"
#include "utils/log.h"
#include "utils/hex/Consts.h"

namespace decorator {
  
Mover::Mover() noexcept :
  Decorator(),
  _target(),
  _dir(),
  _tolerance(0.01),
  _speed(0.01)
{
  
}

void Mover::walk(IWorldMap& map) noexcept {
  /* Trivial exit */
  if (_target.empty()) {
    _status = Status::TargetReached;
    return;
  }
  const WorldObject::Position oldpos(_entity->obj().pos());
  const WorldObject::Position target(_target.top());
  /* Check if target is reached */
  if (WorldObject::Position::distance(oldpos, target) < _tolerance) {
    unstackTarget();
    if (_target.empty()) {
      _status = Status::TargetReached;
      return;
    }
  }
  /* compute a walk step */
  _entity->obj().pos(oldpos + _dir * _speed);
  Pointer obstacle(nullptr);
  bool validMove(map.tryPosition(_entity, &obstacle));
  /* search for an alternative path */
  if (!validMove) {
    if (!obstacle) {
      LOG_TODO("Implement dodge Borders\n");
      _status = Status::ObstructedPath;
      return;
    }
    /* compute the alternatives */
    WorldObject::Position collide(
      (_entity->obj().pos() - obstacle->obj().pos()).unit());
    WorldObject::Position esc1(collide * hex::RMatrix_C60A);
    WorldObject::Position esc2(collide * hex::RMatrix_CC60A);
    WorldObject::Position& esc = esc1;
    /* get the most direct one */
    if (WorldObject::Position::distance(oldpos + esc2 * _speed, target) 
      < WorldObject::Position::distance(oldpos + esc1 * _speed, target)) 
    {
      esc = esc2;
    }
    /* stack a circumvention of obstacle */
    _entity->obj().pos(oldpos + collide * _speed);
    stackTarget(oldpos + esc * obstacle->obj().radius());
  }
  /* update object's position if required */
  if (oldpos.tile() != _entity->obj().pos().tile()) {
    const WorldObject::Position newpos(_entity->obj().pos());
    _entity->obj().pos(oldpos);
    map.removeObject(_entity);
    _entity->obj().pos(newpos);
    map.addObject(_entity);
  }
  /* done */
  _status = Status::Walking;
}
  
void Mover::clearPath() noexcept {
  while (!_target.empty()) {
    _target.pop();
  }
}

void 
Mover::setTarget(const WorldObject::Position& target, float tolerance) 
noexcept 
{
  clearPath();
  stackTarget(target);
  _tolerance = tolerance;
}
  
void Mover::stackTarget(const WorldObject::Position& target) noexcept {
  _target.push(target);
  _dir = (target - _entity->obj().pos()).unit();
  _entity->obj().orientation(_dir.orientation());
}
void Mover::unstackTarget() noexcept {
  _target.pop();
  if (!_target.empty()) {
    _dir = (_target.top() - _entity->obj().pos()).unit();
    _entity->obj().orientation(_dir.orientation());
  }
}

Mover::Builder::Builder(
  const Pointer& entity, float speed) 
noexcept : 
  Decorator::Builder(entity),
  _speed(speed)
{
}

void Mover::Builder::operator() (Pointer& ptr) const noexcept {
  this->Decorator::Builder::operator() (ptr);
  Mover& mover(static_cast<Mover&>(*ptr));
  mover._speed = _speed;
}

}