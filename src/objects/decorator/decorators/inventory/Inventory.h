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
/// \file   Inventory.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 13 octobre 2020, 12:40
///

#ifndef INVENTORY_H
#define INVENTORY_H

#include "core/Object.h"
#include "ressources/core/Stack.h"

#include <vector>

namespace decorators {
  
  namespace InventoryEvents {
    struct Modified {};
    struct Full {};
    struct Empty {};
  }
  
  /// \brief Interface decorator for things that store other things
  class Inventory : 
    public core::Object,
    public core::OSubject<
      InventoryEvents::Modified, 
      InventoryEvents::Full, 
      InventoryEvents::Empty>
  {
  public:
    
    /// \brief Unified object to return inventory content
    /// \todo turn it to a polymorphic object with iterator
    using Content = std::vector<Stack>;
    
    bool update() noexcept override { assert(0); }
    
    /// \brief try to add given stack to the inventory
    /// \return garbage aka ressources that cannot be added
    Stack add(const Stack& stack) noexcept {
      Stack garbage(doAdd(stack));
      if (garbage.size() != stack.size()) {
        core::OSubject<InventoryEvents::Modified>::notify();
        if (isFull()) {
          core::OSubject<InventoryEvents::Full>::notify();
        }
      }
      return garbage;
    }
    
    /// \brief try to remove given qty of given type from the inventory
    /// \return quantity successfully removed, can be empty if stack contains
    ///   no such ressources
    Stack reduce(Stack::Ressource type, int qty) noexcept {
      Stack result(doReduce(type, qty));
      if (!result.empty()) {
        core::OSubject<InventoryEvents::Modified>::notify();
        if (isEmpty()) {
          core::OSubject<InventoryEvents::Empty>::notify();
        }
      }
      return result;
    }
    
    /// \brief Must return quantity of given ressource that can be stored
    virtual int storableQtyOf(Stack::Ressource type) const noexcept = 0;
    /// \brief Must return true if inventory is empty
    virtual bool isEmpty() const noexcept = 0;
    /// \brief Must return true if inventory is full
    virtual bool isFull() const noexcept = 0;
    
    /// \brief Must return inventory content
    virtual Content content() const noexcept = 0;
    
  protected:
    
    /// \brief Must Add given stack to the inventory 
    /// \return garbage if full stack cannot be added
    virtual Stack doAdd(const Stack& stack) noexcept = 0;
    /// \brief Must try to get given stack from the inventory
    /// \brief type : Ressource type to take
    /// \brief qty  : Quantity to get, 0 for the maximum available
    /// \return a smaller one if request is bigger than inventory content
    virtual Stack doReduce(Stack::Ressource type, int qty) noexcept = 0;
  };
}

#endif /* INVENTORY_H */