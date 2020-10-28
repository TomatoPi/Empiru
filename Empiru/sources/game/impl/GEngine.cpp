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

namespace game {

IDecoAllocator *IDecoAllocator::_allocator = nullptr;
IOpeAllocator *IOpeAllocator::_allocator = nullptr;

namespace impl {

void GEngine::createEntity(EntityBuilder &builder) noexcept {
  EUID uid(_euidgen.generateUID());
  bool success(_entities.emplace(uid, Entity()).second);
  assert(success);
  builder(uid);
}
IGEngine::Entity& GEngine::getEntity(const EUID uid) noexcept {
  return _entities.at(uid);
}

void GEngine::registerDecorator(const DUID kind, DReg::Allocator *alloc) {
  bool success(_decorators._allocs.emplace(kind, alloc).second);
  assert(success);
}

Decorator::Pointer GEngine::createObject(const DUID kind,
    Decorator::Builder &builder) {
  /* alloc and build */
  Decorator::Pointer ptr(_decorators._allocs.at(kind)->createObject());
  builder(ptr);
  /* subcribe to object discard */
  ptr->Subject<Events::DecoratorDiscarded>::addSubscriber(
      [this](Decorator &deco, Events::DecoratorDiscarded&) -> void {
        _decorators._garbage.emplace_back(deco.ptr());
      });
  /* notify tha worldo */
  auto kinds(DKind::Get().basesOf(kind));
  for (auto kind : kinds) {
    auto callbacks(_decorators._constructCallbacks.at(kind));
    for (auto callback : callbacks) {
      callback(ptr);
    }
  }
  return ptr;
}

void GEngine::destroyGarbadge() {
  for (auto ptr : _decorators._garbage) {
    _decorators._allocs.at(ptr->kind())->deleteObject(ptr);
  }
  for (auto ptr : _operators._garbage) {
    _operators._allocs.at(ptr->kind())->deleteObject(ptr);
  }
}

void GEngine::addCreationSubscriber(const DUID kind,
    std::function<void(Decorator::Pointer ptr)> &&callback) noexcept {
  _decorators._constructCallbacks.at(kind).emplace_back(callback);
}
void GEngine::addDestructionSubscriber(const DUID kind,
    std::function<void(Decorator::Pointer ptr)> &&callback) noexcept {
  _decorators._destructCallbacks.at(kind).emplace_back(callback);
}

void GEngine::registerOperator(const OUID kind, OReg::Allocator *alloc) {
  bool success(_operators._allocs.emplace(kind, alloc).second);
  assert(success);
}

Operator::Pointer GEngine::createObject(const OUID kind,
    Operator::Builder &builder) {
  /* alloc and build */
  Operator::Pointer ptr(_operators._allocs.at(kind)->createObject());
  builder(ptr);
  /* subcribe to object discard */
  ptr->Subject<Events::OperatorDiscarded>::addSubscriber(
      [this](Operator &deco, Events::OperatorDiscarded&) -> void {
        _operators._garbage.emplace_back(deco.ptr());
      });
  /* notify tha worldo */
  auto kinds(OKind::Get().basesOf(kind));
  for (auto kind : kinds) {
    auto callbacks(_operators._constructCallbacks.at(kind));
    for (auto callback : callbacks) {
      callback(ptr);
    }
  }
  return ptr;
}

void GEngine::addCreationSubscriber(const OUID kind,
    std::function<void(Operator::Pointer ptr)> &&callback) noexcept {
  _operators._constructCallbacks.at(kind).emplace_back(callback);
}
void GEngine::addDestructionSubscriber(const OUID kind,
    std::function<void(Operator::Pointer ptr)> &&callback) noexcept {
  _operators._destructCallbacks.at(kind).emplace_back(callback);
}

}  // namespace impl
} /* namespace render */
