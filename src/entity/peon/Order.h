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
/// \file   Order.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 20 septembre 2020, 17:43
///

#ifndef ORDER_H
#define ORDER_H

#include "utils/hex/Axial.h"
#include "utils/world/WorldPtr.h"
#include "utils/world/WorldObject.h"

/// \brief Base class for orders
class Order {
public:
  
  /// \brief Order type
  enum Type {
    Invalid, ///< Invalid Order
    MoveTo,  ///< Move to another position
    Harvest, ///< Harvest some ressources
    Store,   ///< Put some ressources in a storage
  };
  
private:
  
  Type  _type;  ///< Order's type
  
protected:
  
  Order(Type type) : _type(type) {}
  
public:
  
  Order() : _type(Invalid) {}
  virtual ~Order() noexcept = default;
  
  /// \brief return Order's type
  Type type() const noexcept {
    return _type;
  }
  /// \brief return order's target position
  virtual const WorldObject::Position & targetPos() const noexcept = 0;
  /// \brief return true if order target exists
  virtual bool isValid() const noexcept = 0;
};

/// \brief MoveTo order object
class OrderMoveTo : public Order {
private:
  
  WorldObject::Position _target;
  float                 _tolerance;
  
public:
  
  OrderMoveTo(const WorldObject::Position& pos, float tolerance) :
    Order(MoveTo), _target(pos), _tolerance(tolerance)
  {
  }
    
  /// \brief return order's target position
  virtual const WorldObject::Position & targetPos() const noexcept {
    return _target;
  }
  /// \brief return minimal distance at whitch the target will be considered
  ///   as reached
  float tolerance() const noexcept {
    return _tolerance;
  }
  /// \brief return true if order target exists
  virtual bool isValid() const noexcept {
    return true;
  }
};

/// \brief Base class for orders that refers to a WorldObject
class _OrderWorldTarget : public Order {
private:
  
  WorldPtr _target;
  
public:
  
  _OrderWorldTarget(Type type, const WorldPtr& ptr) : 
    Order(type), _target(ptr) 
  {
  }
  
  /// \brief return target for Harvest order
  /// \pre Must be a Harvest Order
  const WorldPtr& target() const {
    return _target;
  }
  /// \brief return order's target position
  virtual const WorldObject::Position & targetPos() const noexcept {
    return _target->pos();
  }
  /// \brief return true if order target exists
  virtual bool isValid() const noexcept {
    return _target.isValid();
  }
};

/// \brief Harvest Order
class OrderHarvest : public _OrderWorldTarget {
public:
  
  OrderHarvest(const WorldPtr& ptr) :
    _OrderWorldTarget(Harvest, ptr)
  {
  }
};

/// \brief Store Order
class OrderStore : public _OrderWorldTarget {
public:
  
  OrderStore(const WorldPtr& ptr) :
    _OrderWorldTarget(Store, ptr)
  {
  }
};

#endif /* ORDER_H */
