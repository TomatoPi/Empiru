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

#include "engine/core/decorator/Decorator.h"
#include "ressources/core/Stack.h"

namespace deco {
  
  /// \brief Interface decorator for things that store other things
  class Inventory : public Decorator {
  public:
    
    /// \brief Unified object to return inventory content
    /// \todo turn it to a polymorphic object with iterator
    typedef std::vector<Stack> Content;
    
    /// \brief Must Add given stack to the inventory 
    /// \return garbage if full stack cannot be added
    virtual Stack add(const Stack& stack) noexcept = 0;
    /// \brief Must try to get given stack from the inventory
    /// \brief type : Ressource type to take
    /// \brief qty  : Quantity to get, 0 for the maximum available
    /// \return a smaller one if request is bigger than inventory content
    virtual Stack reduce(Stack::Ressource type, int qty) noexcept = 0;
    /// \brief Must erase inventory content
    virtual void clear() noexcept = 0;
    
    /// \brief Must return true if given type can be added to the inventory
    virtual bool canStore(Stack::Ressource type) const noexcept = 0;
    /// \brief Must return true if inventory is empty
    virtual bool isEmpty() const noexcept = 0;
    
    /// \brief Must return inventory content
    virtual Content content() const noexcept = 0;
    
    class Builder : public Decorator::Builder {
    public:
      explicit Builder(const EntityPtr& entity) noexcept :
        Decorator::Builder(entity) {}
      
      virtual void operator() (DecoratorPtr& ptr) const noexcept override {
        /// Make the concrete decorator accessible via the Inventory Decorator
        this->Decorator::Builder::operator() (ptr);
        this->addMarkers(ptr, typeid(Inventory));
      }
    };
  };
}
#endif /* INVENTORY_H */

