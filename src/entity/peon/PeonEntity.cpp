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

#include "PeonEntity.h"
#include "entity/decorators/slot/Slot.h"

const decorator::Mover& Peon::mover() const noexcept {
  return static_cast<const decorator::Mover&>(*getDecorator<decorator::Mover>());
}
decorator::Mover& Peon::mover() noexcept {
  return static_cast<decorator::Mover&>(*getDecorator<decorator::Mover>());
}

const decorator::Inventory& Peon::inventory() const noexcept {
  return static_cast<const decorator::Inventory&>(*getDecorator<decorator::Inventory>());
}
decorator::Inventory& Peon::inventory() noexcept {
  return static_cast<decorator::Inventory&>(*getDecorator<decorator::Inventory>());
}

const decorator::Collector& Peon::collector() const noexcept {
  return static_cast<const decorator::Collector&>(*getDecorator<decorator::Collector>());
}
decorator::Collector& Peon::collector() noexcept {
  return static_cast<decorator::Collector&>(*getDecorator<decorator::Collector>());
}

Peon::Builder::Builder(
  GameEngineInterface& engine, 
  const WorldObject::Position& pos) 
noexcept :
  Entity::Builder(WorldObject(WorldObject::Size::Small, 0.05, pos)), _engine(engine)
{
}

void Peon::Builder::operator() (Pointer& ptr) const noexcept {
  this->Entity::Builder::operator ()(ptr);
  decorator::Mover::Builder movbuilder(ptr, 0.01);
  _engine.createDecorator(typeid(decorator::Mover), movbuilder);
  decorator::Slot::Builder invbuilder(ptr, 10);
  _engine.createDecorator(typeid(decorator::Slot), invbuilder);
  decorator::Collector::Builder colbuilder(ptr);
  _engine.createDecorator(typeid(decorator::Collector), colbuilder);
}

#if 0
/// \brief Constructor
Peon::Peon() :
  WorldObject(WorldObject::Size::Small, 0.05), 
  _todo(),
  _dir(),
  _cptr(0),
  _delay(1),
  _paused(true),
  _invetory(),
  _warehouse(nullptr)
{
}

/// \brief Return current peon's target
/// \pre peon has a target (path not empty)
const Order & Peon::currentOrder() const {
  assert(hasOrders());
  return *_todo.front();
}
  
/// \brief ressources qty in peon's inventory
const Stack & Peon::inventory() const {
  return _invetory;
}
/// \brief remove everythings from the inventory
void Peon::clearInventory() {
  _invetory.clear();
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
const hex::Axial & Peon::direction() const {
  return _dir;
}

/// \brief true if path is not empty
bool Peon::hasOrders() const {
  return !_todo.empty();
}
/// \brief true if peon is paused
bool Peon::isPaused() const {
  return _paused;
}

/// \brief remove all path's steps
void Peon::clearOrders() {
  //_dir._x = _dir._y = _dir._z = 0;
  for (auto& order : _todo) {
    delete order;
  }
  _todo.clear();
}
/// \brief add pos on top of path
void Peon::addOrder(Order* order) {
  _todo.emplace_front(order);
}
/// \brief set dir according to top step
void Peon::beginOrder() {
  assert(hasOrders());
  if (!_todo.front()->isValid()) {
    this->endOrder();
    return;
  }
  _dir = Position((_todo.front()->targetPos() - this->pos()).toUnit());
  Order::Type type(_todo.front()->type());
  switch (type) {
  case Order::MoveTo :
    _delay = 1;
    break;
  case Order::Harvest :
    _delay = 60;
    break;
  case Order::Store :
    _delay = 1;
    break;
  case Order::Supply : 
    _delay = 1;
    break;
  case Order::Build : 
    _delay = 1;
    break;
  default :
    assert(0);
  }
  _cptr = _delay-1;
  _paused = false;
}
/// \brief Halt current order excecution
void Peon::pauseOrder() {
  _paused = true;
}
/// \brief remove top step
void Peon::endOrder() {
  assert(hasOrders());
  delete _todo.front();
  _todo.pop_front();
  //_dir._x = _dir._y = _dir._z = 0;
}

/// \brief Attach this peon to a warehouse
void Peon::attachWarehouse(const WorldPtr& ptr) {
  assert(ptr);
  _warehouse = ptr;
}
/// \brief Detach this peon to it's warehouse
void Peon::detachWarehouse() {
  _warehouse = nullptr;
}
const WorldPtr& Peon::attachtedWharehouse() const {
  return _warehouse;
}
/// \brief return current peon's warehouse
WorldPtr Peon::attachtedWharehouse() {
  return _warehouse;
}

/// \brief Increment peon's order counter and return true if order is ready
bool Peon::tickCptr() {
  if (_paused) return false;
  return 0 == (_cptr = (_cptr+1) % _delay);
}
#endif