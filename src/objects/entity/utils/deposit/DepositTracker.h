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
/// \file   DepositBeh.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 19:01
///

#ifndef DEPOSITBEH_H
#define DEPOSITBEH_H

#include "core/Object.h"
#include "core/Observer.h"
#include "DepositEntity.h"

class DepositTracker : public core::Object, public core::Observer {
private:
  
  IGameAllocator& _alloc;
  
public:
  
  explicit DepositTracker(IGameAllocator& engine) noexcept : 
    _alloc(engine) 
  {
    this->registerEvent<GameEvents::ObjectCreated>(
        [this](const GameEvents::ObjectCreated& event) -> void {
          if (typeid(*event._ptr) == typeid(DepositEntity)) {
            event._ptr->subscribe(this->_this);
          }
        });
    this->registerEvent<GameEvents::ObjectDestroyed>(
        [this](const GameEvents::ObjectDestroyed& event) ->void {
          if (typeid(*event._ptr) == typeid(DepositEntity)) {
          }
        });
  }
  virtual ~DepositTracker() noexcept = default;

  virtual bool operator() () noexcept override {assert(0);};
  /// \brief Must be called on events
  virtual void 
  doOnNotify(const core::Pointer& p, const Event& e) noexcept override {
    if (typeid(e) == typeid(decorators::Inventory::Event)) {
      if (static_cast<const decorators::Inventory::Event&>(e).type 
      == decorators::Inventory::Event::Type::Empty) 
      {
        _alloc.discardObject(p);
      }
    }
  }
};

#endif /* DEPOSITBEH_H */

