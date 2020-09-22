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

#include "utils/hex/HexCoords.h"
#include "utils/world/WorldRef.h"

/// \brief Holder of Peon's orders informations
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
  
  /// \brief Order's target
  union Target {
    Target();                 ///< Constructor
    FlatHexPosition _move;    ///< MoveTo order's target
    WorldRef *      _harvest; ///< Harvest order's target
    struct {
      WorldRef *_storage;
    } _store;                 ///< Store order's target
  } _target;                  ///< Order's target
  
  Type _type; ///< Order's type
  
public:
  
  /// \brief return a MoveTo Order
  static Order moveTo(const FlatHexPosition & pos);
  /// \brief return an Harvest Order
  static Order harvest(WorldRef *obj);
  /// \brief return a Store Order
  static Order store(WorldRef *obj);  
  /// \brief Constructor
  Order();
  
  /// \brief return Order's type
  Type type() const;
  
  /// \brief return order target
  /// \pre Order must have a target (!Invalid)
  const FlatHexPosition & targetPos() const;
  
  /// \brief return target for MoveTo order
  /// \pre Must be a MoveTo Order
  const FlatHexPosition & targetMove() const;
  /// \brief return target for Harvest order
  /// \pre Must be a Harvest Order
  WorldRef * targetHarvest() const;
  
  /// \brief return target for Store order
  /// \pre Must be a Store order
  WorldRef * targetStore() const;
};

#endif /* ORDER_H */
