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
/// \file   Order.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 20 septembre 2020, 17:43
///

#include <cassert>
#include <cstring>

#include "Order.h"
  
/// \brief return a MoveTo Order
Order Order::moveTo(const WorldObject::Position & pos, float tol) {
  Order order;
  order._target._move._target = pos;
  order._target._move._tolerance = tol;
  order._type = MoveTo;
  return order;
}
/// \brief return an Harvest Order
Order Order::harvest(WorldRef *obj) {
  Order order;
  order._target._harvest = obj;
  order._type = Harvest;
  return order;
}
/// \brief return a Store Order
Order Order::store(WorldRef *obj) {
  Order order;
  order._target._store._storage = obj;
  order._type = Store;
  return order;
}

/// \brief Order's target's constructor
Order::Target::Target() {
}

/// \brief Constructor
Order::Order() : _target(), _type(Invalid) {}

/// \brief return Order's type
Order::Type Order::type() const {
  return _type;
}

const WorldObject::Position & Order::targetPos() const {
  switch (_type) {
  case MoveTo : return _target._move._target;
  case Harvest : return (**_target._harvest).pos();
  case Store : return (**_target._store._storage).pos();
  default :
    assert(0);
  }
}

/// \brief return target for MoveTo order
/// \pre Must be a MoveTo Order
const WorldObject::Position & Order::targetMove() const {
  assert(_type == MoveTo);
  return _target._move._target;
}
float Order::moveTolerance() const {
  assert(_type == MoveTo);
  return _target._move._tolerance;
}
/// \brief return target for Harvest order
/// \pre Must be a Harvest Order
WorldRef * Order::targetHarvest() const {
  assert(_type == Harvest);
  return _target._harvest;
}

/// \brief return target for Store order
/// \pre Must be a Store order
WorldRef * Order::targetStore() const {
  assert(_type == Store);
  return _target._store._storage;
}