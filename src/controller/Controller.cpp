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

#include "entity/peon/Peon.h"
#include "utils/log.h"
#include "entity/tree/Tree.h"
#include "utils/world/Storage.h"
#include "utils/hex/Conversion.h"
#include <cmath>

/// \brief Constructor
Controller::Controller(
            WorldInterface & w, 
            GameEngine & g, 
            RenderingEngine & rdr, 
            SoundEngine & s) :
  _world(w), _state(w, g, rdr),
  _soundEngine(s)
{
  
}
  
/// \brief Called when a left click is performed at given position
void Controller::leftClickOn(const WorldObject::Position & click, WorldRef *obj) {
  // Update controller according to result
  if (obj) {
    if (auto peon = dynamic_cast<Peon*>(&**obj)) {
      _state.selectPeon(obj);
      _soundEngine.playRandomSound(0);
      LOG_DEBUG("Peon : Inventory : %d %d\n", 
          peon->inventory().type(), peon->inventory().size());
    }
    else {
      _state.deselectPeon();
      if (obj) {
        if (auto harvest = dynamic_cast<Harvestable*>(&**obj)) {
          LOG_DEBUG("Ressource : %s : %d\n", 
              typeid(*harvest).name(), harvest->size());
        }
        else if (auto storage = dynamic_cast<Storage*>(&**obj)) {
          LOG_DEBUG("Storage : %s : %s\n", 
              typeid(*storage).name(), storage->content_str().c_str());
        }
      }
    }
  } else {
    _state.deselectPeon();
  }
}
/// \brief Called when a right click is performed at given position
void Controller::rightClickOn(const WorldObject::Position & click, WorldRef *obj) {
  // If there is a selected peon and click is valid, let's go
  if (_state.selectedPeon() != nullptr && _world.isOnMap(click)) {
    Peon & peon(static_cast<Peon &>(**_state.selectedPeon()));
    if (obj) {
      if (auto harvest = dynamic_cast<Harvestable *>(&**obj)) {
        if (peon.canHarvest(harvest->type())) {
          peon.clearOrders();
          peon.addOrder(Order::harvest(obj));
          peon.beginOrder();
          _soundEngine.playRandomSound(0);
        }
      }
      else if (auto storage = dynamic_cast<Storage *>(&**obj)) {
        if (!peon.inventory().empty()) {
          peon.clearOrders();
          peon.addOrder(Order::store(obj));
          peon.beginOrder();
          _soundEngine.playRandomSound(0);
        }
      }
    } else {
      peon.clearOrders();
      peon.addOrder(Order::moveTo(click));
      peon.beginOrder();
    }
  }
}