/*
 * Copyright (C) 2020 Alexis
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

/* 
 * File:   peon.cpp
 * Author: Alexis CORREIA HENRIQUES <alex2ikangame@gmail.com>
 * 
 * Created on 10 septembre 2020, 16:08
 */

#include <cassert>

#include "Peon.h"

Peon::Peon(const FlatHexPosition & pos) : 
  WorldObject(pos, 0.05), 
  _path(),
  _dir()
{
  
}

const FlatHexPosition & Peon::target() const {
  assert(hasPath());
  return _path.front();
}
const FlatHexPosition & Peon::direction() const {
  return _dir;
}

bool Peon::hasPath() const {
  return !_path.empty();
}
void Peon::clearPath() {
  _dir._x = _dir._y = _dir._z = 0;
  _path.clear();
}
void Peon::addStep(const FlatHexPosition & pos) {
  _path.emplace_front(pos);
}
void Peon::beginStep() {
  assert(hasPath());
  _dir = FlatHexPosition(this->pos(), _path.front()).toUnit();
}
void Peon::endstep() {
  assert(hasPath());
  this->pos(_path.front());
  _path.pop_front();
  _dir._x = _dir._y = _dir._z = 0;
}