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
/// \file   Controller.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 12 septembre 2020, 08:51
/// \brief Core object for user control
///

#include "Controller.h"

#include "utils/log.h"
#include "entity/peon/Peon.h"
#include "utils/world/Harvestable.h"
#include "utils/world/Storage.h"
#include "events/ControllerEvents.h"

/// \brief Constructor
Controller::Controller(WorldInterface & w) noexcept :
  _selection(nullptr), _world(w)
{
}
  
/// \brief Called when a left click is performed at given position
void Controller::leftClickOn(const WorldObject::Position & click, WorldRef *obj) {
  // Update controller according to result
  if (_selection) {
    sendNotification(EventObjectDeselected(_selection));
  }
  if (obj) {
    _selection = obj;
    sendNotification(EventObjectSelected(_selection));
  } else {
    _selection = nullptr;
  }
}
/// \brief Called when a right click is performed at given position
void Controller::rightClickOn(const WorldObject::Position & click, WorldRef *obj) {
  // If there is a selected peon and click is valid, let's go
  if (_selection != nullptr && _world.isOnMap(click)) {
    Peon * peon(dynamic_cast<Peon *>(&**_selection));
    if (!peon) {
      return;
    }
    if (obj) {
      if (auto harvest = dynamic_cast<Harvestable *>(&**obj)) {
        if (peon->canHarvest(harvest->type())) {
          peon->clearOrders();
          peon->addOrder(Order::harvest(obj));
          peon->beginOrder();
          sendNotification(EventObjectAction(_selection, obj));
        }
      }
      else if (auto storage = dynamic_cast<Storage *>(&**obj)) {
        if (!peon->inventory().empty() 
          && storage->canStore(peon->inventory().type())) 
        {
          peon->clearOrders();
          peon->addOrder(Order::store(obj));
          peon->beginOrder();
          sendNotification(EventObjectAction(_selection, obj));
        }
      }
    } else {
      peon->clearOrders();
      peon->addOrder(Order::moveTo(click));
      peon->beginOrder();
      sendNotification(EventObjectAction(_selection, nullptr));
    }
  }
}