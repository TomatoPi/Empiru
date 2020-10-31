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
/// \file   GameControllerInterface.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 06:10
///
#ifndef GAMECONTROLLERINTERFACE_H
#define GAMECONTROLLERINTERFACE_H

#include <observer/SuperObserver.h>
#include <world/Position.h>
#include <game/EUID.h>

namespace ctrl {

namespace Events {

struct ObjectSelected {
  const game::EUID uid;
  ObjectSelected(const game::EUID uid) noexcept :
      uid(uid) {
  }
};

struct ObjectDeselected {
  const game::EUID uid;
  ObjectDeselected(const game::EUID uid) noexcept :
      uid(uid) {
  }
};

}  // namespace Events

class IGameCtrl: public SuperObserver::Subject<IGameCtrl,
    Events::ObjectSelected, Events::ObjectDeselected> {
  static IGameCtrl *_instance;
public:

  template<typename E>
  using Subject = SuperObserver::Subject<IGameCtrl, E>; // @suppress("Invalid template argument")

  static void registerController(IGameCtrl *ctrl) noexcept {
    _instance = ctrl;
  }
  static IGameCtrl& Get() noexcept {
    return *_instance;
  }

  virtual ~IGameCtrl() noexcept = default;

  virtual void selectObject(const game::EUID) noexcept = 0;
  virtual void deselectObject(const game::EUID) noexcept = 0;

  virtual const game::EUID& selection() const noexcept = 0;
  virtual const world::Position& cursor() const noexcept = 0;
};

}

#endif /* GAMECONTROLLERINTERFACE_H */

