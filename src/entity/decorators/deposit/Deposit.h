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
/// \file   Deposit.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 19:02
///

#ifndef DEPOSIT_H
#define DEPOSIT_H

#include "entity/decorators/inventory/Inventory.h"
#include "ressources/core/Stack.h"

#include <cassert>

namespace decorator {

  class Deposit : public Inventory {
  private:

    Stack _stack;
    int   _difficulty;

  public:

    Deposit() noexcept : _stack() {}
    virtual ~Deposit() noexcept = default;
    
    int difficulty() const noexcept {
      return _difficulty;
    }
    
    /// \brief Must return true if given type can be added to the inventory
    virtual int storableQtyOf(Stack::Ressource type) const noexcept override {
      return 0;
    }
    /// \brief Must return true if inventory is empty
    virtual bool isEmpty() const noexcept override {
      return _stack.empty();
    }
    virtual bool isFull() const noexcept override {
      return _stack.full();
    }
    
    /// \brief Must return inventory content
    virtual Content content() const noexcept override {
      return Content{_stack};
    }
    
  protected:
    
    /// \brief Must Add given stack to the inventory 
    /// \return garbage if full stack cannot be added
    virtual Stack doAdd(const Stack& stack) noexcept override {
      assert(0 && "invalid operation");
      return Stack();
    }
    /// \brief Must try to get given stack from the inventory
    /// \brief type : Ressource type to take
    /// \brief qty  : Quantity to get, 0 for the maximum available
    /// \return a smaller one if request is bigger than inventory content
    virtual Stack doReduce(Stack::Ressource type, int qty) noexcept override {
      assert(type == _stack.type());
      return _stack.reduce(qty);
    }

  public:

    class Builder : public Inventory::Builder {
    private:

      int              _difficulty;
      int              _size;
      Stack::Ressource _type;

    public :

      explicit Builder(
        const EntityPtr& entity, 
        Stack::Ressource type, int size, int difficulty)
      noexcept;

      virtual void operator() (Pointer& ptr) const noexcept override;
    };
  };
}
#endif /* DEPOSIT_H */
