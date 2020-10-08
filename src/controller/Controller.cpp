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
#include "entity/buildings/site/ConstructSite.h"

/// \brief Constructor
Controller::Controller(WorldInterface& w, GameEngine& engine) noexcept :
  Subject(), Observer(),
  _world(w), _engine(engine), 
  _selection(nullptr),
  _cursor(),
  _status(StateFlag::NoSelection)
{
    this->registerEvent<EventObjectDestroyed>(
        [this](const EventObjectDestroyed& event) -> void {
          if (event._ptr == _selection) {
            switch (_status) {
            case StateFlag::NoSelection :
              assert(0 && "Invalid State");
              break;
            case StateFlag::ObjectSelected :
              _selection = nullptr;
              _status = StateFlag::NoSelection;
              break;
            case StateFlag::BuildGhost :
              _selection = nullptr;
              _status = StateFlag::NoSelection;
              break;
            default:
              assert(0 && "Invalid State");
            }
          }
        });
}

void Controller::selectObject(WorldPtr& ptr) noexcept {
  _selection = ptr;
  sendNotification(EventObjectSelected(_selection));
}
void Controller::deselectObject() noexcept {
  sendNotification(EventObjectDeselected(_selection));
  _selection = nullptr;
}
void Controller::objectAction(WorldPtr& ptr) noexcept {
  if (Peon * peon = dynamic_cast<Peon *>(&*_selection)) {
    if (ptr) {
      if (Harvestable* harvest = dynamic_cast<Harvestable*>(&*ptr)) {
        if (peon->canHarvest(harvest->type())) {
          peon->clearOrders();
          peon->addOrder(new OrderHarvest(ptr));
          peon->beginOrder();
          sendNotification(EventObjectAction(_selection, ptr));
        }
      }
      else if (Storage* storage = dynamic_cast<Storage*>(&*ptr)) {
        if (storage->canStore(peon->inventory().type())) {
          peon->attachWarehouse(ptr);
          peon->addOrder(new OrderStore(ptr));
          peon->beginOrder();
          sendNotification(EventObjectAction(_selection, ptr));
        }
        else {
          if (peon->attachtedWharehouse() == ptr) {
            peon->detachWarehouse();
          }
          else {
            peon->attachWarehouse(ptr);
          }
        }
      } 
      else if (ConstructionSite* site = dynamic_cast<ConstructionSite*>(&*ptr)) {
        if (site->need(peon->inventory())) {
          peon->addOrder(new OrderSupply(ptr));
          peon->beginOrder();
          sendNotification(EventObjectAction(_selection, ptr));
        } 
        else if (site->isFilled()) {
          peon->addOrder(new OrderBuild(ptr));
          peon->beginOrder();
          sendNotification(EventObjectAction(_selection, ptr));
        }
      }
    } 
    else {
      peon->clearOrders();
      peon->addOrder(new OrderMoveTo(_cursor, 0.01));
      peon->beginOrder();
      sendNotification(EventObjectAction(_selection, WorldPtr(nullptr)));
    } 
  }
}
void Controller::createGhost(const std::type_info& type) noexcept {
  ConstructionGhost::Builder builder(type, _cursor.tile());
  _selection = _engine.createObject(typeid(ConstructionGhost), builder);
  sendNotification(EventObjectSelected(_selection));
}
void Controller::destroyGhost() noexcept {
  assert(typeid(*_selection) == typeid(ConstructionGhost));
  sendNotification(EventObjectDeselected(_selection));
  _engine.removeObject(_selection);
  _selection = nullptr;
}
void Controller::createBuildSite() noexcept {
  ConstructionGhost& ghost = static_cast<ConstructionGhost&>(*_selection);
  sendNotification(EventObjectDeselected(_selection));
  ConstructionSite::Builder builder(ghost);
  WorldPtr site(_engine.createObject(typeid(ConstructionSite), builder));
  _engine.removeObject(_selection);
  _selection = site;
  sendNotification(EventObjectSelected(_selection));
}
bool Controller::updateGhost() noexcept {
  _world.removeObject(_selection);
  _selection->pos(_cursor.tile());
  _world.addObject(_selection);
  /* set the valid flag depending on tile content */
  /*  an empty tile */
  const Tile::Content* tile = _world.getContentAt(_selection->pos());
  static_cast<ConstructionGhost&>(*_selection).valid(
        tile && (tile->size() == 1));
  return static_cast<ConstructionGhost&>(*_selection).valid();
}
  
/// \brief Called when a left click is performed at given position
void Controller::leftClickOn(const WorldObject::Position& click, WorldPtr& ptr) {
  _cursor = click;
  switch (_status) {
    
  case StateFlag::NoSelection :
    if (!ptr) return;
    selectObject(ptr);
    _status = StateFlag::ObjectSelected;
    break;
    
  case StateFlag::ObjectSelected :
    if (!ptr) {
      deselectObject();
      _status = StateFlag::NoSelection;
    }
    else {
      deselectObject();
      selectObject(ptr);
    }
    break;
    
  case StateFlag::BuildGhost :
    if (updateGhost()) {
      createBuildSite();
      _status = StateFlag::ObjectSelected;
    }
    break;
    
  default:
    assert(0);
  }
}
/// \brief Called when a right click is performed at given position
void Controller::rightClickOn(const WorldObject::Position& click, WorldPtr& ptr) {
  _cursor = click;
  switch (_status) {
    
  case StateFlag::NoSelection :
    /* nothing */
    break;
    
  case StateFlag::ObjectSelected :
    objectAction(ptr);
    break;
    
  case StateFlag::BuildGhost :
    destroyGhost();
    _status = StateFlag::NoSelection;
    break;
    
  default:
    assert(0);
  }
}

/// \brief Called when a building has been selected
void Controller::selectConstructionGhost(const std::type_info& type) {
  switch (_status) {
    
  case StateFlag::BuildGhost :
    destroyGhost();
    
  case StateFlag::NoSelection :
  case StateFlag::ObjectSelected :
    
    createGhost(type);
    updateGhost();
    _status = StateFlag::BuildGhost;
    break;
    
  default:
    assert(0);
  }
}

/// \brief Called when the mouse has moved, maximum one time at each frame
///   Only the last position is passed to this function
void Controller::cursorMoved(const WorldObject::Position& click, int x, int y) {
  _cursor = click;
  switch (_status) {
    
  case StateFlag::NoSelection :
  case StateFlag::ObjectSelected :
    /* nothing */
    break;
    
  case StateFlag::BuildGhost :
    updateGhost();
    _status = StateFlag::BuildGhost;
    break;
    
  default:
    assert(0);
  }
}

/// \brief Return the current position of the cursor
const WorldObject::Position& Controller::cursor() const noexcept {
  return _cursor;
}