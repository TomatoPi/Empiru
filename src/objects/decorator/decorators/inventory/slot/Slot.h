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
/// \file   Slot.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 14 octobre 2020, 15:16
///

#ifndef SLOT_H
#define SLOT_H

#include "../Inventory.h"
#include <cassert>

namespace decorator {
  
  /// \brief Interface decorator for things that store other things
  class Slot : public Inventory {
  private:
    
    Stack _stack;
    int   _max;
    
  public:
    
    Slot() noexcept = default;
    virtual ~Slot() noexcept = default;
    
    /// \brief Must return quantity of given ressource that can be stored
    virtual int storableQtyOf(Stack::Ressource type) const noexcept override {
      if (_stack.empty()) {
        return _max;
      }
      if (_stack.type() != type) {
        return 0;
      }
      return _stack.max() - _stack.size();
    }
    
    /// \brief Must return inventory content
    virtual Content content() const noexcept override {
      if (_stack.empty()) {
        return Content();
      }
      return Content{_stack};
    }
    
    /// \brief Must return true if inventory is empty
    virtual bool isEmpty() const noexcept override {
      return _stack.empty();
    }
    virtual bool isFull() const noexcept override {
      return _stack.full();
    }
    
  protected:
    
    /// \brief Must Add given stack to the inventory 
    /// \return garbage if full stack cannot be added
    virtual Stack doAdd(const Stack& stack) noexcept override {
      if (_stack.empty()) {
        _stack = Stack(stack.type(), 0, _max);
      }
      assert(_stack.type() == stack.type());
      return _stack.add(stack);
    }
    /// \brief Must try to get given stack from the inventory
    /// \brief type : Ressource type to take
    /// \brief qty  : Quantity to get, 0 for the maximum available
    /// \return a smaller one if request is bigger than inventory content
    virtual Stack doReduce(Stack::Ressource type, int qty) noexcept override {
      assert(_stack.type() == type);
      return _stack.reduce(qty);
    }
    
  public:
    
    class Builder : public Inventory::Builder {
    private:
      int _max;
    public:
      explicit Builder(int max) noexcept :
        Inventory::Builder(), _max(max) {}
      
      virtual void operator() (core::Pointer& ptr) const noexcept override {
        /// Make the concrete decorator accessible via the Inventory Decorator
        this->Inventory::Builder::operator() (ptr);
        Slot& slot(static_cast<Slot&>(*ptr));
        slot._max = _max;
      }
    };
  };
}

#endif /* SLOT_H */

