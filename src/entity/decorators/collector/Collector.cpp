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
/// \file   Collector.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 14 octobre 2020, 11:36
///

#include "Collector.h"
#include "entity/decorators/deposit/Deposit.h"

namespace decorator {

  void Collector::collectAt(const DecoratorPtr& ptr, Stack::Ressource type)   
  noexcept {
    _target = type;
    _action = Action::Collect;
    setWorkSite(ptr);
  }
  void Collector::storeAt(const DecoratorPtr& ptr, Stack::Ressource type)   
  noexcept {
    _target = type;
    _action = Action::Store;
    setWorkSite(ptr);
  }

  void Collector::workChanged() noexcept {
    if (_action == Action::Collect) {
      if (Deposit* deposit = dynamic_cast<Deposit*>(&*_worksite)) {
        _cptr = Counter(deposit->difficulty());
        return;
      } 
    }
    _cptr = Counter(0);
  }
  void Collector::doWork() noexcept {
    if (_cptr.tick() != 0) {
      return;
    }
    Inventory& site(static_cast<Inventory&>(*_worksite));
    Inventory& inventory(static_cast<Inventory&>(*_inventory));
    if (_action == Action::Collect) {
      int qty = std::min(inventory.storableQtyOf(_target), 1);
      if (!qty) {
        _status = Status::WorkDone;
        return;
      }
      Stack res = site.reduce(_target, qty);
      if (res.empty()) {
        _status = Status::WorkDone;
        return;
      }
      res = inventory.add(res);
      assert(res.empty());
    }
    else {
      int qty = std::min(site.storableQtyOf(_target), 1);
      if (!qty) {
        _status = Status::WorkDone;
        return;
      }
      Stack res = inventory.reduce(_target, qty);
      if (res.empty()) {
        _status = Status::WorkDone;
        return;
      }
      res = site.add(res);
      assert(res.empty());
    }
  }
  bool Collector::isWorkDone() const noexcept {
    if (_action == Action::Collect) {
      return !static_cast<const Inventory&>(*_inventory).storableQtyOf(_target);
    }
    else {
      return !static_cast<const Inventory&>(*_worksite).storableQtyOf(_target);
    }
  }

  Collector::Builder::Builder(const EntityPtr& entity) noexcept :
    Worker::Builder(entity) {}

  void Collector::Builder::operator() (DecoratorPtr& ptr) const noexcept {
    this->Worker::Builder::operator() (ptr);
    Collector& collector(static_cast<Collector&>(*ptr));
    collector._inventory = collector._entity->getDecorator<Inventory>();
  }
}