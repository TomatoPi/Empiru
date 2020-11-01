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
/// \file   GEngine.h
/// \author tomato
///
/// \date 28 oct. 2020 16:36:38
///
#ifndef SOURCES_GAME_IMPL_GENGINE_H_
#define SOURCES_GAME_IMPL_GENGINE_H_

#include "../IGEngine.h"
#include "../IAllocator.h"
#include "../IDecoAllocator.h"
#include "../IOpeAllocator.h"

#include <world/IMap.h>
#include <render/IREngine.h>

#include <alloc/Allocator.h>
#include <functional>
#include <unordered_map>
#include <set>
#include <cassert>

namespace game {
namespace impl {

template<typename T, typename DiscardE>
struct ConcreteAllocator: public game::IAllocator<T, DiscardE> {

  template<typename E>
  using TSub = typename T::Subject<E>;
  using Allocator = alloc::IAllocator<T, typename T::Pointer>;
  using AllocTable = std::unordered_map<typename T::Kind,Allocator*>; // @suppress("Invalid template argument")
  using Callback = std::function<void(typename T::Pointer)>;
  using CSTable = std::unordered_map<typename T::Kind,std::list<Callback>>; // @suppress("Invalid template argument")
  using DSTable = std::unordered_map<typename T::Kind,std::list<Callback>>; // @suppress("Invalid template argument")
  using Garbage = std::set<typename T::Pointer>;

  AllocTable _allocs;
  Garbage _garbage;
  CSTable _constructCallbacks;
  DSTable _destructCallbacks;

  virtual ~ConcreteAllocator() noexcept = default;

  void registerObject(const typename T::Kind kind, Allocator *alloc) {
    _constructCallbacks.emplace(kind, std::list<Callback>()); // @suppress("Method cannot be resolved")
    _destructCallbacks.emplace(kind, std::list<Callback>()); // @suppress("Method cannot be resolved")
    /* create allocator for concrete types */
    if (nullptr != alloc) {
      bool success(_allocs.emplace(kind, alloc).second); // @suppress("Method cannot be resolved")
      assert(success);
    }
  }

  typename T::Pointer createObject(typename T::Builder &builder) override {
    /* alloc and build */
    typename T::Pointer ptr(_allocs.at(builder.kind)->createObject()); // @suppress("Method cannot be resolved")
    builder(ptr);
    /* subcribe to object discard */
    ptr->TSub < DiscardE > ::addSubscriber([this](T &deco, DiscardE&) -> void { // @suppress("Type cannot be resolved") // @suppress("Function cannot be resolved")
      _garbage.emplace(deco.ptr());
    });
    /* notify tha worldo */
    auto kinds(T::Hierarchy().basesOf(builder.kind));
    for (auto kind : kinds) {
      auto callbacks(_constructCallbacks.at(kind)); // @suppress("Method cannot be resolved")
      for (auto callback : callbacks) {
        callback(ptr);
      }
    }
    return ptr;
  }

  void destroyGarbadge() override {
    for (auto ptr : _garbage) {
      _allocs.at(ptr->kind())->deleteObject(ptr); // @suppress("Method cannot be resolved")
    }
    _garbage.clear();
  }

  void addCreationSubscriber(const typename T::Kind kind,
      std::function<void(typename T::Pointer ptr)> &&callback) noexcept
          override {
    _constructCallbacks.at(kind).emplace_back(callback); // @suppress("Method cannot be resolved")
  }
  void addDestructionSubscriber(const typename T::Kind kind,
      std::function<void(typename T::Pointer ptr)> &&callback) noexcept
          override {
    _destructCallbacks.at(kind).emplace_back(callback); // @suppress("Method cannot be resolved")
  }
};

class GEngine final : public IGEngine, public ConcreteAllocator<Decorator,
    Events::DecoratorDiscarded>, public ConcreteAllocator<Operator,
    Events::OperatorDiscarded> {
private:

  using DecoAlloc = ConcreteAllocator<Decorator, Events::DecoratorDiscarded>;
  using OpeAlloc = ConcreteAllocator<Operator, Events::OperatorDiscarded>;
  using ETable = std::unordered_map<EUID, Entity>; // @suppress("Invalid template argument")
  EUID::IDGen _euidgen;
  ETable _entities;

public:

  GEngine() noexcept = default;
  virtual ~GEngine() noexcept = default;

  const EUID createEntity(EntityBuilder &builder) noexcept override final;
  void discardEntity(const EUID uid) noexcept override final;
  Entity& getEntity(const EUID uid) noexcept override final;
  Decorator::Pointer findDecorator(const EUID uid, const Decorator::Kind kind) noexcept override final;
  void bindStrict(const EUID uid, Decorator::Pointer ptr) noexcept override final;
  void bindWide(const EUID uid, Decorator::Pointer ptr) noexcept override final;
  void unbindStrict(const EUID, Decorator::Pointer) noexcept override final;
  void unbindWide(const EUID, Decorator::Pointer) noexcept override final;

  void update() noexcept;

  void destroyGarbadge() override final;

  void registerDecorator(const Decorator::Kind kind,
      DecoAlloc::Allocator *alloc);
  void registerOperator(const Operator::Kind kind, OpeAlloc::Allocator *alloc);

private:

  void bindAs(const EUID uid, Decorator::Pointer ptr, Decorator::Kind as) noexcept;
  void unbindAs(const EUID uid, Decorator::Pointer ptr, Decorator::Kind as) noexcept;
};

}  // namespace impl
} /* namespace render */

#endif /* SOURCES_GAME_IMPL_GENGINE_H_ */
