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

#include "engine/core/entity/Entity.h"
#include "engine/events/GameEvents.h"
#include "controller/events/ControllerEvents.h"

#include <cassert>

namespace {
  class NullEntityController : public EntityControllerInterface {
  private:
    Controller& _controller;
  public:
    NullEntityController(Controller& c) noexcept : _controller(c) {}
    
    virtual void leftClickOn(EntityPtr ptr) noexcept override {
      /* nothing */
    }
    virtual void leftClickOut(EntityPtr ptr) noexcept override {
      if (ptr) {
        _controller.selectObject(ptr);
      }
    }
    virtual void RightClickOn(EntityPtr ptr) noexcept override {
      /* nothing */
    }
    virtual void RightClickOut(EntityPtr ptr) noexcept override {
      /* nothing */
    }
    virtual void cursorMoved() noexcept override {
      /* nothing */
    }
    virtual void deselected(EntityPtr ptr) noexcept override {
      /* nothing */
    }
  };
  
  const std::type_info& NullType = typeid(nullptr);
}

/// \brief Constructor
Controller::Controller() noexcept :
  GameControllerInterface(), BigSubject(), BigObserver(),
  _controllers(),
  _selection(nullptr),
  _cursor()
{
  this->registerController(NullType, new NullEntityController(*this));
  this->registerEvent<EventObjectDestroyed>(
      [this](const EventObjectDestroyed& event) -> void {
        if (event._ptr == _selection) {
          _selection = nullptr;
        }
      });
}

void Controller::selectObject(EntityPtr ptr) noexcept {
  get(_selection).deselected(_selection);
  _selection = ptr;
  sendNotification(EventObjectSelected(_selection));
}
void Controller::deselectObject(EntityPtr ptr) noexcept {
  assert(ptr == _selection);
  sendNotification(EventObjectDeselected(_selection));
  get(_selection).deselected(_selection);
  _selection = nullptr;
}
void Controller::objectAction(EntityPtr ptr, EntityPtr target) noexcept {
  sendNotification(EventObjectAction(ptr, target));
}
const EntityPtr& Controller::selection() const noexcept {
  return _selection;
}
/// \brief Return the current position of the cursor
const WorldObject::Position& Controller::cursor() const noexcept {
  return _cursor;
}

/// \brief Called when a left click is performed at given position
void Controller::leftClickOn(
  const WorldObject::Position& click, const EntityPtr& ptr) 
{
  _cursor = click;
  if (ptr == _selection) {
    get(_selection).leftClickOn(_selection);
  }
  else {
    get(_selection).leftClickOut(ptr);
    get(ptr).leftClickOn(ptr);
  }
}
/// \brief Called when a right click is performed at given position
void Controller::rightClickOn(
  const WorldObject::Position& click, const EntityPtr& ptr) 
{
  _cursor = click;
  if (ptr == _selection) {
    get(_selection).RightClickOn(_selection);
  }
  else {
    get(_selection).RightClickOut(ptr);
    get(ptr).RightClickOn(ptr);
  }
}

/// \brief Called when the mouse has moved, maximum one time at each frame
///   Only the last position is passed to this function
void Controller::cursorMoved(const WorldObject::Position& click, int x, int y) {
  _cursor = click;
  get(_selection).cursorMoved();
}

  
void Controller::registerController(
  const std::type_info& type, 
  EntityControllerInterface*&& controller) 
noexcept
{
  bool success(_controllers.emplace(type, controller).second);
  assert(success);
}

EntityControllerInterface& Controller::get(const EntityPtr& ptr) noexcept {
  return *_controllers.at(ptr.isValid() ? typeid(*ptr) : NullType);
}

#if 0
void Controller::objectAction(EntityPtr& ptr) noexcept {
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
      sendNotification(EventObjectAction(_selection, EntityPtr(nullptr)));
    } 
  }
}
void Controller::createGhost(const std::type_info& type) noexcept {
  ConstructionGhost::Builder builder(type, _cursor.tile());
  _selection = _engine.createEntity(typeid(ConstructionGhost), builder);
  sendNotification(EventObjectSelected(_selection));
}
void Controller::destroyGhost() noexcept {
  assert(typeid(*_selection) == typeid(ConstructionGhost));
  sendNotification(EventObjectDeselected(_selection));
  _engine.discardEntity(_selection);
  _selection = nullptr;
}
void Controller::createBuildSite() noexcept {
  ConstructionGhost& ghost = static_cast<ConstructionGhost&>(*_selection);
  sendNotification(EventObjectDeselected(_selection));
  ConstructionSite::Builder builder(ghost);
  EntityPtr site(_engine.createEntity(typeid(ConstructionSite), builder));
  _engine.discardEntity(_selection);
  _selection = site;
  sendNotification(EventObjectSelected(_selection));
}
bool Controller::updateGhost() noexcept {
  _world.removeObject(_selection);
  _selection->position().pos(_cursor.tile());
  _world.addObject(_selection);
  /* set the valid flag depending on tile content */
  /*  an empty tile */
  const Tile::Content* tile = _world.getContentAt(_selection->pos());
  static_cast<ConstructionGhost&>(*_selection).valid(
        tile && (tile->size() == 1));
  return static_cast<ConstructionGhost&>(*_selection).valid();
}
#endif