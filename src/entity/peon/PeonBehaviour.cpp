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
/// \file   PeonBehaviour.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 18 septembre 2020, 19:18
///

#include <cassert>

#include "PeonBehaviour.h"

#include "utils/hex/Consts.h"
#include "utils/log.h"
#include "entity/tree/Tree.h"
#include "utils/world/Storage.h"
#include "utils/world/Recipe.h"
#include "utils/world/Recipe.h"
#include "entity/buildings/site/ConstructSite.h"

/// \brief Must compute one behaviour tick of obj
void PeonBehaviour::tick(WorldObject& obj, WorldPtr& ptr, MapInterface& world) {
  Peon & peon(static_cast<Peon &>(obj));
  // Pass if nothing to do
  if (!peon.hasOrders()) return;
  // if order is not ready
  if (!peon.tickCptr()) return;
  // else let's do things
  switch (peon.currentOrder().type()) {
  case Order::MoveTo :
    moveTo(peon, ptr, world);
    break;
  case Order::Harvest :
    harvest(peon, ptr, world);
    break;
  case Order::Store :
    store(peon, ptr, world);
    break;
  case Order::Supply :
    supply(peon, ptr, world);
    break;
  case Order::Build :
    build(peon, ptr, world);
    break;
  default:
    assert(0);
  }
}

/// \brief compute harvest order
void PeonBehaviour::build(Peon& peon, WorldPtr& ptr, MapInterface& world) {
  const OrderBuild& order(static_cast<const OrderBuild&>(peon.currentOrder()));
  WorldPtr obj(order.target());
  // check if target always exists
  if (!obj) {
    peon.endOrder();
    return;
  }
  // If too far, walk
  if (obj->radius() + peon.radius() + 0.15
    < WorldObject::Position::distance(peon.pos(), obj->pos())) 
  {
    peon.addOrder(new OrderMoveTo(obj->pos(), obj->radius() + peon.radius() + 0.1));
    peon.beginOrder();
    return;
  }
  // Move the peon in the site
  ConstructionSite& site(static_cast<ConstructionSite&>(*obj));
  world.removeObject(ptr);
  site.addWorker(ptr);
  peon.clearOrders();
}

/// \brief compute harvest order
void PeonBehaviour::supply(Peon& peon, WorldPtr& ptr, MapInterface& world) {
  const OrderSupply& order(static_cast<const OrderSupply&>(peon.currentOrder()));
  WorldPtr obj(order.target());
  // check if target always exists
  if (!obj) {
    peon.endOrder();
    return;
  }
  // If too far, walk
  if (obj->radius() + peon.radius() + 0.15
    < WorldObject::Position::distance(peon.pos(), obj->pos())) 
  {
    peon.addOrder(new OrderMoveTo(obj->pos(), obj->radius() + peon.radius() + 0.1));
    peon.beginOrder();
    return;
  }
  // Put the inventory in the warehouse
  Recipe& recipe(dynamic_cast<Recipe&>(*obj));
  Stack residue(recipe.supply(peon.inventory()));
  peon.clearInventory();
  peon.addToInventory(residue.type(), residue.size());
  peon.endOrder();
}

/// \brief compute harvest order
void PeonBehaviour::store(Peon& peon, WorldPtr& ptr, MapInterface& world) {
  const OrderStore& order(static_cast<const OrderStore&>(peon.currentOrder()));
  WorldPtr obj(order.target());
  // check if target always exists
  if (!obj) {
    if (peon.attachtedWharehouse() == obj) {
      peon.detachWarehouse();
    }
    peon.endOrder();
    return;
  }
  // If too far, walk
  if (obj->radius() + peon.radius() + 0.15
    < WorldObject::Position::distance(peon.pos(), obj->pos())) 
  {
    peon.addOrder(new OrderMoveTo(obj->pos(), obj->radius() + peon.radius() + 0.1));
    peon.beginOrder();
    return;
  }
  // Put the inventory in the warehouse
  Storage & storage(dynamic_cast<Storage &>(*obj));
  storage.addToStorage(peon.inventory());
  peon.clearInventory();
  peon.endOrder();
}

/// \brief compute harvest order
void PeonBehaviour::harvest(Peon& peon, WorldPtr& ptr, MapInterface& world) {
  const OrderHarvest& order(static_cast<const OrderHarvest&>(peon.currentOrder()));
  WorldPtr obj(order.target());
  // check if target always exists
  if (!obj) {
    peon.endOrder();
    return;
  }
  // If too far, walk
  if (obj->radius() + peon.radius() + 0.15
    < WorldObject::Position::distance(peon.pos(), obj->pos())) 
  {
    peon.addOrder(new OrderMoveTo(obj->pos(), obj->radius() + peon.radius() + 0.1));
    peon.beginOrder();
    return;
  }
  // Yes we are ready to take some Wouuuuuuud
  Harvestable & harvest(dynamic_cast<Harvestable &>(*obj));
  if (peon.inventory().size() >= 10) {
    if (peon.attachtedWharehouse()) {
      peon.addOrder(new OrderStore(peon.attachtedWharehouse()));
      peon.beginOrder();
    } else {
      peon.pauseOrder();
    }
  } else {
    int qty(harvest.reduce(1));
    if (qty) {
      peon.addToInventory(harvest.type(), qty);
    } else {
      peon.pauseOrder();
    }
  }
}

/// \brief compute path order for the peon
void PeonBehaviour::moveTo(Peon& peon, WorldPtr& ptr, MapInterface& world) {
  // Let's get it started
  const WorldObject::Position oldpos(peon.pos());
  const OrderMoveTo& order(static_cast<const OrderMoveTo&>(peon.currentOrder()));
  // If target is reached we're done
  if (WorldObject::Position::distance(oldpos, order.targetPos()) < order.tolerance()) {
    peon.endOrder();
    if (!peon.hasOrders()) 
       return;
    peon.beginOrder();
  } 
  // Else compute one step
  else {
    // Compute default new position
    peon.pos(WorldObject::Position(oldpos + peon.direction() * 0.01));
    // Check validity
    WorldObject *obstacle(nullptr);
    bool validMove(tryPosition(peon, ptr, &obstacle, world));
    // Try to find alternative path
    if (!validMove) {
      // World limit
      if (!obstacle) {
        LOG_TODO("Escape World Borders\n");
      } 
      // Round obstacle
      else {
        WorldObject::Position collide((peon.pos() - obstacle->pos()).unit());
        WorldObject::Position esc1(collide * hex::RMatrix_C60A);
        WorldObject::Position esc2(collide * hex::RMatrix_CC60A);
        WorldObject::Position & esc = esc1;
        if (
            WorldObject::Position::distance(oldpos + esc2 * 0.01, order.targetPos()) 
          < WorldObject::Position::distance(oldpos + esc1 * 0.01, order.targetPos())) 
        {
          esc = esc2;
        }
        peon.pos(oldpos + collide * 0.01);
        peon.addOrder(new OrderMoveTo(oldpos + esc * obstacle->radius() , 0.01));
        peon.beginOrder();
        validMove = true;
      }
    }
    if (validMove) {
      // If tile has changed move peon
      if (oldpos.tile() != peon.pos().tile()) {
        WorldObject::Position tmp(peon.pos());
        peon.pos(oldpos);
        world.removeObject(ptr);
        peon.pos(tmp);
        world.addObject(ptr);
      }
    } else {
      /// \todo Add notification if impossible path
      peon.pos(oldpos);
      peon.clearOrders();
    }
  } /* else compute one step */
}

/// \brief Return true if given position is valid
///   if position is invalid, return false and return pointer to the obstacle
///   in 'obstacle' if relevant
bool PeonBehaviour::tryPosition(
        Peon& peon, 
        WorldPtr& ptr, 
        WorldObject** obstacle, 
        MapInterface& world)
const {
  // Check validity
  if (!world.isOnMap(peon.pos())) {
    return false;
  }
  // Check collisions
  bool valid(true);
  peon.pos().mapNeightbours(
    [&]
    (const WorldObject::Position & pos) -> bool {
      auto content = world.getContentAt(pos);
      if (content != nullptr){
        for (auto obj : *content){
          if (obj == ptr) 
            continue;
          if (obj->collide(peon)) {
            *obstacle = &*obj;
            valid = false;
            return true;
          }
        }
      }
      return false;
    });
  return valid;
}