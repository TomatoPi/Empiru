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
/// \file   Collector.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 22:18
///

#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <deque>
#include "engine/core/decorator/Decorator.h"
#include "ressources/core/Stack.h"
#include "entity/decorators/mover/Mover.h"

class CollectorDecorator : public Decorator {
public:
  
  enum class Action {
    None,
    FillStorage,
    DumpStorage,
  };
  
  enum class Status {
    Idle,
    Acting,
    TooFar,
  };
  
private:
  
  DecoratorPtr  _collectSite;
  DecoratorPtr  _storageSite;
  Stack         _inventory;
  int           _invMax;
  Action        _action;
  Status        _status;
  
public:

  CollectorDecorator() noexcept : _inventory() {}
  virtual ~CollectorDecorator() noexcept = default;
  
  void setCollectSite(const DecoratorPtr& ptr) noexcept;
  void setStorageSite(const DecoratorPtr& ptr) noexcept;
  
  const Stack& inventory() const noexcept {return _inventory;}
  void inventory(const Stack& s) noexcept {_inventory = s;}
  bool inventoryFull() const noexcept {return _invMax <= _inventory.size();}
  
  Status status() const noexcept {return _status;}
  DecoratorPtr target() const noexcept;
  
  void giveAction(Action action) noexcept;
  void updateStatus() noexcept;
  
  void tick() noexcept;
  
public:
  
  class Builder : public Decorator::Builder {
  public :
    
    explicit Builder(const EntityPtr& entity) noexcept :
      Decorator::Builder(entity) {}
    
    virtual void operator() (DecoratorPtr& ptr) const noexcept override {
      this->Decorator::Builder::operator() (ptr);
    }
  };
};

#endif /* COLLECTOR_H */
