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
#include "entity/buildings/site/ConstructionGhost.h"

/// \brief Constructor
Controller::Controller(WorldInterface& w, GameEngine& engine) noexcept :
  _world(w), _engine(engine), 
  _selection(nullptr),
  _cursor()
{
}
  
/// \brief Called when a left click is performed at given position
void Controller::leftClickOn(const WorldObject::Position& click, WorldPtr& ptr) {
  // Update controller according to result
  if (_selection) {
    if (typeid(*_selection) == typeid(ConstructionGhost)) {
      ConstructionGhost& ghost = static_cast<ConstructionGhost&>(*_selection);
      return;
    } /* if selection is ghost */
    sendNotification(EventObjectDeselected(_selection));
  }
  if (ptr) {
    _selection = ptr;
    sendNotification(EventObjectSelected(_selection));
  } else {
    _selection = nullptr;
  }
}
/// \brief Called when a right click is performed at given position
void Controller::rightClickOn(const WorldObject::Position& click, WorldPtr& ptr) {
  // If there is a selected peon and click is valid, let's go
  if (_selection && _world.isOnMap(click)) {
    
    if (Peon * peon = dynamic_cast<Peon *>(&*_selection)) {
      peonRightClick(peon, click, ptr);
      return;
    }
    else if (typeid(*_selection) == typeid(ConstructionGhost)) {
      _engine.removeObject(_selection);
      _selection = nullptr;
    }
  }
}
void Controller::peonRightClick(
  Peon *peon, 
  const WorldObject::Position& click, 
  WorldPtr& ptr) 
{
  if (ptr) {
    if (auto harvest = dynamic_cast<Harvestable *>(&*ptr)) {
      if (peon->canHarvest(harvest->type())) {
        peon->clearOrders();
        peon->addOrder(new OrderHarvest(ptr));
        peon->beginOrder();
        sendNotification(EventObjectAction(_selection, ptr));
      }
    }
    else if (auto storage = dynamic_cast<Storage *>(&*ptr)) {
      peon->attachWarehouse(ptr);
      if (!peon->inventory().empty() 
        && storage->canStore(peon->inventory().type())) 
      {
        peon->addOrder(new OrderStore(ptr));
        peon->beginOrder();
        sendNotification(EventObjectAction(_selection, ptr));
      }
    }
  } else {
    peon->clearOrders();
    peon->addOrder(new OrderMoveTo(click, 0.01));
    peon->beginOrder();
    sendNotification(EventObjectAction(_selection, nullptr));
  }
}

/// \brief Called when a building has been selected
void Controller::selectConstructionGhost(const std::type_info& type) {
  /* potentialy deselect object */
  if (_selection) {
    sendNotification(EventObjectDeselected(_selection));
    if (typeid(*_selection) == typeid(ConstructionGhost)) {
      _engine.removeObject(_selection);
    }
    _selection = nullptr;
  }
  /* create a new ghost */
  ConstructionGhost::Builder builder(type, _cursor.tile());
  _selection = _engine.createObject(typeid(ConstructionGhost), builder);
  sendNotification(EventObjectSelected(_selection));
}

/// \brief Called when the mouse has moved, maximum one time at each frame
///   Only the last position is passed to this function
void Controller::cursorMoved(const WorldObject::Position& click, int x, int y) {
  sendNotification(EventCursorMoved(click, x, y));
  /* if current selection is a ghost */
  if (_selection && (typeid(ConstructionGhost) == typeid(*_selection))) {
    _world.removeObject(_selection);
    _selection->pos(click.tile());
    _world.addObject(_selection);
    /* set the valid flag depending on tile content */
    /*  an empty tile */
    const Tile::Content* tile = _world.getContentAt(_selection->pos());
    static_cast<ConstructionGhost&>(*_selection).valid(
          tile && (tile->size() == 1));
  }
  _cursor = click;
}

/// \brief Return the current position of the cursor
const WorldObject::Position& Controller::cursor() const noexcept {
  return _cursor;
}