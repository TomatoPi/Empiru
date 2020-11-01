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

#include <game/IDecoAllocator.h>
#include <builtin/game/inventory/Inventory.h>
#include <builtin/game/inventory/storage/Storage.h>

namespace tribe {

TribeInfos::TribeInfos() noexcept :
    _stocks() {
  using Storage = builtin::game::inventory::Storage;
  using Inventory = builtin::game::inventory::Inventory;
  using EventModified = builtin::game::inventory::Events::Modified;
  game::IDecoAllocator::Get().addCreationSubscriber(Storage::TypeID(),
      [this](game::Decorator::Pointer ptr) -> void {
        /* when a storage is created, listen for modifications */
        ptr->as<Inventory>().Inventory::Subject<EventModified>::addSubscriber(
            [this](Inventory&, EventModified &event) -> void {
              grow(event.type, event.diff);
            });
        /* when a storage is removed, we remove contained ressources */
        ptr->game::Decorator::Subject<game::Events::DecoratorDiscarded>::addSubscriber(
            [this](game::Decorator &deco,
                game::Events::DecoratorDiscarded&) -> void {
              for (const items::Stack &stack : deco.as<Inventory>().content()) {
                grow(stack.type(), -stack.size());
              }
            });
      });
}

items::Stack TribeInfos::getOrAdd(items::Ressource type) noexcept {
  TribeStocks::iterator itr(_stocks.find(items::Stack(type)));
  if (itr == _stocks.end()) {
    return *_stocks.emplace(type).first;
  }
  return *itr;
}
void TribeInfos::grow(items::Ressource type, int qty) noexcept {
  items::Stack tmp(getOrAdd(type));
  if (qty > 0) {
    tmp.add(items::Stack(type, qty));
  } else {
    tmp.reduce(qty);
  }
  _stocks.erase(tmp);
  _stocks.emplace(tmp);
}

}  // namespace tribe
