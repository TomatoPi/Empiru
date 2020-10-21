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
#include "engine/core/entity/Entity.h"
#include "entity/decorators/storage/Storage.h"


TribeInfos::TribeInfos() noexcept :
  _objects(), _stocks(), _cptr(30)
{    
  this->registerEvent<EventObjectCreated>(
    [this](const EventObjectCreated& event) -> void {
      if (decorator::Pointer ptr = event._ptr->getDecorator<decorator::Storage>()) {
        bool res(_objects.emplace(ptr).second);
        assert(res);
      }
    });
  this->registerEvent<EventObjectDestroyed>(
    [this](const EventObjectDestroyed& event) -> void {
      if (decorator::Pointer ptr = event._ptr->getDecorator<decorator::Storage>()) {
        auto itr(_objects.find(ptr));
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
    for (auto& stack : static_cast<const decorator::Storage&>(*ptr).content()) {
      addStack(stack);
    }
  }
}