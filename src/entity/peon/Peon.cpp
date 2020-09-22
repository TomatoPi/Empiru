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

/// 
/// \file   Peon.cpp
/// \author Alexis CORREIA HENRIQUES <alex2ikangame@gmail.com>
///
/// \date 10 septembre 2020, 16:08
/// \brief The ultimate worker, useful to make anything you can think of
///

#include <cassert>

#include "Peon.h"

/// \brief Constructor
Peon::Peon() :
  WorldObject(0.05), 
  _todo(),
  _dir(),
  _cptr(0),
  _delay(1),
  _invetory()
{
}

/// \brief Return current peon's target
/// \pre peon has a target (path not empty)
const Order & Peon::currentOrder() const {
  assert(hasOrders());
  return _todo.front();
}
  
/// \brief ressources qty in peon's inventory
const Stack & Peon::inventory() const {
  return _invetory;
}
/// \brief add ressources to peon's inventory
void Peon::addToInventory(Stack::Ressource type, int qty) {
  assert(canHarvest(type));
  if (_invetory.empty()) {
    _invetory = Stack(type, qty);
  } else {
    _invetory.reduce(-qty);
  }
}

/// \brief return true if type is harvestable
bool Peon::canHarvest(Stack::Ressource type) const {
  return _invetory.empty() || _invetory.type() == type;
}

/// \brief Return current peon's orientation
const FlatHexPosition & Peon::direction() const {
  return _dir;
}

/// \brief true if path is not empty
bool Peon::hasOrders() const {
  return !_todo.empty();
}
/// \brief remove all path's steps
void Peon::clearOrders() {
  //_dir._x = _dir._y = _dir._z = 0;
  _todo.clear();
}
/// \brief add pos on top of path
void Peon::addOrder(const Order & order) {
  _todo.emplace_front(order);
}
/// \brief set dir according to top step
void Peon::beginOrder() {
  assert(hasOrders());
  _dir = FlatHexPosition(this->pos(), _todo.front().targetPos()).toUnit();
  switch(_todo.front().type()) {
  case Order::MoveTo :
    _delay = 1;
    break;
  case Order::Harvest :
    _delay = 60;
    break;
  default :
    assert(0);
  }
  _cptr = _delay-1;
}
/// \brief remove top step
void Peon::endOrder() {
  assert(hasOrders());
  _todo.pop_front();
  //_dir._x = _dir._y = _dir._z = 0;
}

/// \brief Increment peon's order counter and return true if order is ready
bool Peon::tickCptr() {
  return 0 == (_cptr = (_cptr+1) % _delay);
}