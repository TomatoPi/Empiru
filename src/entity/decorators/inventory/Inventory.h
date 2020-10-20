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
#include <vector>
#include <set>

namespace decorator {
  
  /// \brief Interface decorator for things that store other things
  class Inventory : public Decorator {
  public:
    
    enum class Event {
      Modified,
      Full,
      Empty
    };
    
    class Observer {
    public:
      virtual void onNotify(const DecoratorPtr& ptr, Event event) noexcept = 0;
    };
    
  private:
    
    std::set<DecoratorPtr, alloc::PtrComp> _observers;
    
  protected:
    
    void notify(const DecoratorPtr& ptr, Event event) noexcept {
      for (auto observer : _observers) {
        dynamic_cast<Observer&>(*observer).onNotify(ptr, event);
      }
    }
    
  public:
    
    void attach(const DecoratorPtr& ptr) noexcept {
      _observers.emplace(ptr);
    }
    
    void detach(const DecoratorPtr& ptr) noexcept {
      _observers.erase(ptr);
    }
    
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
    
    /// \brief Must return quantity of given ressource that can be stored
    virtual int storableQtyOf(Stack::Ressource type) const noexcept = 0;
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

