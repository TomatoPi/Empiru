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
/// \file   GEngine.cpp
/// \author tomato
///
/// \date 28 oct. 2020 16:36:38
///
#include <game/impl/GEngine.h>
#include <game/IDecoAllocator.h>
#include <game/IOpeAllocator.h>
#include <log/log.h>

namespace game {

IGEngine *IGEngine::_instance = nullptr;

namespace impl {

const EUID GEngine::createEntity(EntityBuilder &builder) noexcept {
  EUID uid(builder.kind, _euidgen.generateUID());
  bool success(_entities.emplace(uid, Entity()).second); // @suppress("Field cannot be resolved") // @suppress("Method cannot be resolved")
  assert(success);
  builder(uid);
  return uid;
}
void GEngine::discardEntity(const EUID uid) noexcept {
  LOG::debug("Discard entity :", uid);
  Entity &entity(_entities.at(uid)); // @suppress("Method cannot be resolved")
  for (auto& [kind, deco] : entity) { // @suppress("Symbol is not resolved")
    deco->discard(); // @suppress("Method cannot be resolved")
  }
  world::IMap::Get().getObject(uid).discard();
  render::IREngine::Get().getTarget(uid).discard();
  _entities.erase(uid); // @suppress("Method cannot be resolved")
}
IGEngine::Entity& GEngine::getEntity(const EUID uid) noexcept { // @suppress("Member declaration not found")
  return _entities.at(uid); // @suppress("Method cannot be resolved")
}
void GEngine::bindStrict(const EUID uid, Decorator::Pointer ptr) noexcept {
  bindAs(uid, ptr, ptr->kind());
}
void GEngine::bindWide(const EUID uid, Decorator::Pointer ptr) noexcept {
  auto bases(Decorator::Hierarchy().basesOf(ptr->kind()));
  for (Decorator::Kind kind : bases) {
    bindAs(uid, ptr, kind);
  }
}
void GEngine::bindAs(const EUID uid, Decorator::Pointer ptr,
    Decorator::Kind as) noexcept {
  bool success(_entities.at(uid).emplace(as, ptr).second); // @suppress("Method cannot be resolved") // @suppress("Field cannot be resolved")
  assert(success);
}

void GEngine::unbindStrict(const EUID uid, Decorator::Pointer ptr) noexcept {
  unbindAs(uid, ptr, ptr->kind());
}
void GEngine::unbindWide(const EUID uid, Decorator::Pointer ptr) noexcept {
  auto bases(Decorator::Hierarchy().basesOf(ptr->kind()));
  for (Decorator::Kind kind : bases) {
    unbindAs(uid, ptr, kind);
  }
}
void GEngine::unbindAs(const EUID uid, Decorator::Pointer ptr,
    Decorator::Kind as) noexcept {
  _entities.at(uid).erase(as); // @suppress("Method cannot be resolved") // @suppress("Field cannot be resolved")
}

void GEngine::update() noexcept {
  for (auto [kind, alloc] : OpeAlloc::_allocs) { // @suppress("Symbol is not resolved")
    alloc->foreach([](Operator &op) -> void { // @suppress("Method cannot be resolved")
      op.update();
    });
  }
}

void GEngine::destroyGarbadge() {
  DecoAlloc::destroyGarbadge(); // @suppress("Function cannot be resolved")
  OpeAlloc::destroyGarbadge();
}

void GEngine::registerDecorator(const Decorator::Kind kind,
    DecoAlloc::Allocator *alloc) {
  DecoAlloc::registerObject(kind, alloc);
}
void GEngine::registerOperator(const Operator::Kind kind,
    OpeAlloc::Allocator *alloc) {
  OpeAlloc::registerObject(kind, alloc);
}

}  // namespace impl
} /* namespace render */
