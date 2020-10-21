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
/// \file   TribeInfos.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 10 octobre 2020, 01:17
///


#include "TribeInfos.h"
#include "engine/events/GameEvents.h"
#include "objects/decorator/decorators/inventory/storage/Storage.h"


TribeInfos::TribeInfos() noexcept :
  _objects(), _stocks(), _cptr(30)
{    
  this->registerEvent<GameEvents::ObjectCreated>(
    [this](const GameEvents::ObjectCreated& event) -> void {
      if (auto store = dynamic_cast<const decorators::Storage *>(&*event._ptr)) {
        bool res(_objects.emplace(event._ptr).second);
        assert(res);
      }
    });
  this->registerEvent<GameEvents::ObjectDestroyed>(
    [this](const GameEvents::ObjectDestroyed& event) -> void {
      if (auto store = dynamic_cast<const decorators::Storage *>(&*event._ptr)) {
        auto itr(_objects.find(event._ptr));
        assert(itr != _objects.end());
        _objects.erase(itr);
      }
    });
}
void TribeInfos::update() noexcept {
  if (_cptr.tick()) {
    return;
  }
  init();
  for (auto& ptr : _objects) {
    for (auto& stack : static_cast<const decorators::Storage&>(*ptr).content()) {
      addStack(stack);
    }
  }
}