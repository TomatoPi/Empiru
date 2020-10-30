/*
 * Copyright (C) 2020 tomato
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
/// \file   Deposit.h
/// \author tomato
///
/// \date 29 oct. 2020 21:22:06
///
#ifndef SOURCES_BUILTIN_GAME_DEPOSIT_DEPOSITE_H_
#define SOURCES_BUILTIN_GAME_DEPOSIT_DEPOSITE_H_

#include <game/Entity.h>
#include <game/IGEngine.h>
#include <game/IDecoAllocator.h>
#include <builtin/game/inventory/Inventory.h>
#include <builtin/game/inventory/deposit/Deposit.h>

namespace builtin {
namespace game {
namespace deposit {

struct Builder: public ::game::EntityBuilder {

  items::Ressource type;
  int difficulty;
  int qty;

  virtual ~Builder() noexcept = default;
  void operator()(const ::game::EUID uid) noexcept override {
    this->::game::EntityBuilder::operator ()(uid);
    builtin::game::inventory::Deposit::Builder builder;
    /* decorator */
    builder.entity = uid;
    builder.kind = builtin::game::inventory::Deposit::TypeID();
    /* deposit */
    builder.size = qty;
    builder.type = type;
    builder.difficulty = difficulty;
    /* create */
    ::game::Decorator::Pointer inv(
        ::game::IDecoAllocator::Get().createObject(builder));
    inv->as<builtin::game::inventory::Inventory>().Inventory::Subject<
        builtin::game::inventory::Events::Empty>::addSubscriber( // @suppress("Method cannot be resolved")
        [uid](builtin::game::inventory::Inventory&,
            builtin::game::inventory::Events::Empty&) -> void {
          ::game::IGEngine::Get().discardEntity(uid);
        });
    ::game::IGEngine::Get().bindWide(uid, inv);
  }
};

}  // namespace deposit
}  // namespace game
}  // namespace builtin

#endif /* SOURCES_BUILTIN_GAME_DEPOSIT_DEPOSITE_H_ */
