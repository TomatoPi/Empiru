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
/// \file   Peon.h
/// \author Alexis CORREIA HENRIQUES <alex2ikangame@gmail.com>
///
/// \date 10 septembre 2020, 16:08
/// \brief The ultimate worker, useful to make anything you can think of
///

#ifndef PEON_ENTITY_H
#define PEON_ENTITY_H

#include <deque>
#include "objects/entity/core/Entity.h"
#include "engine/core/IGameAllocator.h"

namespace peon {
  class PEntity : public Entity {
  private:
    
    core::Pointer _pos;
    
  public:
    
    PEntity() noexcept = default;
    virtual ~PEntity() noexcept = default;
    
    class Builder : public Entity::Builder {
    public:
      Builder(IGameAllocator& alloc, const world::Position& pos) noexcept;
      virtual void operator() (core::Pointer& ptr) const noexcept override;
    };
  };
}

/*
/// \brief The ultimate worker, useful to make anything you can think of
/// \todo revise the path system
class Peon : public Entity {
public:
  
  const decorator::Mover& mover() const noexcept;
  decorator::Mover& mover() noexcept;
  
  const decorator::Inventory& inventory() const noexcept;
  decorator::Inventory& inventory() noexcept;
  
  const decorator::Collector& collector() const noexcept;
  decorator::Collector& collector() noexcept;
  
  class Builder : public Entity::Builder {
  private:
    
    IGameEngine& _engine;
    
  public:
    
    Builder(IGameEngine& engine, const WorldObject::Position& pos) noexcept;
    virtual void operator() (Pointer& ptr) const noexcept override;
  };
};

private:

  /// \brief Store the list of targets positions, used as a stack
  typedef std::deque<Order*> TodoList;
  
  TodoList   _todo;      ///< stack of pending orders
  hex::Axial _dir;       ///< Peon's orientation
  
  int        _cptr;      ///< Peon's order cptr
  int        _delay;     ///< Peon's order duration
  bool       _paused;    ///< True if peon's order is paused
  Stack      _invetory;  ///< Peon's inventory
  
  WorldPtr  _warehouse; ///< Warehouse this peon is attached to

public:

  /// \brief Constructor
  Peon();
  Peon(const Peon &) = default;
  Peon & operator= (const Peon &) = default;
  
  /// \brief Return current peon's orientation
  const hex::Axial & direction() const;
  
  /// \brief Return current peon's order
  /// \pre peon has an order (stack not empty)
  const Order & currentOrder() const;
  
  const Stack & inventory() const;     ///< ressources qty in peon's inventory
  void clearInventory();               ///< remove everythings from the inventory
  void addToInventory(
    Stack::Ressource type, int qty);   ///< add ressources to peon's inventory
  bool canHarvest(
    Stack::Ressource type) const;      ///< return true if type is harvestable

  bool hasOrders() const;              ///< true if orders is not empty
  bool isPaused() const;               ///< true if peon is paused
  
  void clearOrders();                  ///< remove all orders
  void addOrder(Order* order);  ///< add order on top of the todolist
  void beginOrder();                   ///< set dir according to top order
  void endOrder();                     ///< remove top order
  void pauseOrder();                   ///< Halt current order excecution
  
  void attachWarehouse(const WorldPtr& ptr);  ///< Attach this peon to a warehouse
  void detachWarehouse();                     ///< Detach this peon to it's warehouse
  const WorldPtr& attachtedWharehouse() const;///< return current peon's warehouse
  WorldPtr attachtedWharehouse();             ///< return current peon's warehouse
  
  /// \brief Increment peon's order counter and return true if order is ready
  bool tickCptr();
*/

#endif /* PEON_ENTITY_H */