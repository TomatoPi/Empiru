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

#include <game/IGEngine.h>
#include <cassert>

namespace {
class NullEntityController: public ctrl::IEntityCtrl {
public:
  NullEntityController() noexcept = default;
  virtual ~NullEntityController() noexcept = default;

  void leftClickOn(const game::EUID) noexcept override final {
    /* nothing */
  }
  void leftClickOut(const game::EUID uid) noexcept override final {
    if (uid) {
      ctrl::IGameCtrl::Get().selectObject(uid);
    }
  }
  void RightClickOn(const game::EUID) noexcept override final {
    /* nothing */
  }
  void RightClickOut(const game::EUID) noexcept override final {
    /* nothing */
  }
  void cursorMoved() noexcept override final {
    /* nothing */
  }
  void deselected(const game::EUID) noexcept override final {
    /* nothing */
  }
};

const game::EUID NullType = game::EUID(game::EUID::Hierarchy().newKind(), 0);
}

namespace ctrl {

namespace impl {

SelectHandleDecorator::SelectHandleDecorator() noexcept :
    game::Decorator(nullptr) {
}
const game::Decorator::Kind SelectHandleDecorator::TypeID() noexcept {
  static game::Decorator::Kind _kind(game::Decorator::Hierarchy().newKind());
  return _kind;
}

/// \brief Constructor
Controller::Controller() noexcept :
    IGameCtrl(), _controllers(), _selection(), _cursor(), _selectDecorator(
        new alloc::WrapHandle<SelectHandleDecorator, game::Decorator>()) {
  /* register null controller */
  registerEntityController(NullType.kind(), new NullEntityController());
  /* create decorator handle */
  _selectDecorator->lateBindThis(_selectDecorator);
  game::Decorator::Builder builder;
  builder.entity = NullType;
  builder.kind = SelectHandleDecorator::TypeID();
  builder(_selectDecorator);
  _selectDecorator->game::Decorator::Subject<game::Events::DecoratorDiscarded>::addSubscriber(
      [this](game::Decorator &obj, game::Events::DecoratorDiscarded&) -> void {
        _selection = NullType;
        obj.as<SelectHandleDecorator>().uid = NullType;
      });
}

void Controller::selectObject(const game::EUID uid) noexcept {
  get(_selection).deselected(_selection);
  game::IGEngine::Get().unbindStrict(_selection, _selectDecorator);
  _selection = uid;
  game::IGEngine::Get().bindStrict(uid, _selectDecorator);
  Subject<Events::ObjectSelected>::notify(_selection);
}
void Controller::deselectObject(const game::EUID uid) noexcept {
  assert(uid == _selection);
  Subject<Events::ObjectDeselected>::notify(uid);
  get(uid).deselected(uid);
  game::IGEngine::Get().unbindStrict(uid, _selectDecorator);
  _selectDecorator->as<SelectHandleDecorator>().uid = NullType;
  _selection = NullType;
}
const game::EUID& Controller::selection() const noexcept {
  return _selection;
}
/// \brief Return the current position of the cursor
const world::Position& Controller::cursor() const noexcept {
  return _cursor;
}

/// \brief Called when a left click is performed at given position
void Controller::leftClickOn(const world::Position &click,
    const game::EUID uid) noexcept {
  _cursor = click;
  if (uid == _selection) {
    get(_selection).leftClickOn(_selection);
  } else {
    get(_selection).leftClickOut(uid);
    get(uid).leftClickOn(uid);
  }
}
/// \brief Called when a right click is performed at given position
void Controller::rightClickOn(const world::Position &click,
    const game::EUID uid) noexcept {
  _cursor = click;
  if (uid == _selection) {
    get(_selection).RightClickOn(_selection);
  } else {
    get(_selection).RightClickOut(uid);
    get(uid).RightClickOn(uid);
  }
}

/// \brief Called when the mouse has moved, maximum one time at each frame
///   Only the last position is passed to this function
void Controller::cursorMoved(const world::Position &click, int x,
    int y) noexcept {
  _cursor = click;
  get(_selection).cursorMoved();
}

void Controller::registerEntityController(const game::EUID::Kind kind,
    IEntityCtrl *&&controller) noexcept {
  bool success(_controllers.emplace(kind, controller).second);
  assert(success);
}

IEntityCtrl& Controller::get(const game::EUID uid) noexcept {
  return *_controllers.at(uid.kind());
}

}  // namespace impl

}  // namespace ctrl

#if 0
void Controller::objectAction(Pointer& ptr) noexcept {
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
      sendNotification(EventObjectAction(_selection, Pointer(nullptr)));
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
  Pointer site(_engine.createEntity(typeid(ConstructionSite), builder));
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
