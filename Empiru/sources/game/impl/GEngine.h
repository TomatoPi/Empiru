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
#include "../IDecoAllocator.h"
#include "../IOpeAllocator.h"

#include <alloc/Allocator.h>
#include <unordered_map>

namespace game {
namespace impl {


class GEngine final : public IGEngine,
    public IDecoAllocator,
    public IOpeAllocator {
private:

  template<typename ID, typename T>
  struct Register {
    using Allocator = alloc::IAllocator<T, typename T::Pointer>;
    using AllocTable = std::unordered_map<ID,Allocator*>;
    using Callback = std::function<void(typename T::Pointer)>;
    using CSTable = std::unordered_map<ID,std::list<Callback>>;
    using DSTable = std::unordered_map<ID,std::list<Callback>>;
    using Garbage = std::vector<typename T::Pointer>;

    AllocTable _allocs;
    Garbage _garbage;
    CSTable _constructCallbacks;
    DSTable _destructCallbacks;
  };

  using DReg = Register<DUID, Decorator>;
  using OReg = Register<OUID, Operator>;
  using ETable = std::unordered_map<EUID, Entity>;

  DReg _decorators;
  OReg _operators;
  uid::UIDGenerator _euidgen;
  ETable _entities;

public:

  GEngine() noexcept = default;
  virtual ~GEngine() noexcept = default;

  void createEntity(EntityBuilder &builder) noexcept override final;
  Entity& getEntity(const EUID uid) noexcept override final;

  void registerDecorator(const DUID, DReg::Allocator*);

  Decorator::Pointer createObject(const DUID, Decorator::Builder&)
      override final;

  void destroyGarbadge() override final;

  void addCreationSubscriber(const DUID,
      std::function<void(Decorator::Pointer ptr)>&&) noexcept override final;
  void addDestructionSubscriber(const DUID,
      std::function<void(Decorator::Pointer ptr)>&&) noexcept override final;

  void registerOperator(const OUID, OReg::Allocator*);

  Operator::Pointer createObject(const OUID, Operator::Builder&) override final;

  void addCreationSubscriber(const OUID,
      std::function<void(Operator::Pointer ptr)>&&) noexcept override final;
  void addDestructionSubscriber(const OUID,
      std::function<void(Operator::Pointer ptr)>&&) noexcept override final;
};

}  // namespace impl
} /* namespace render */

#endif /* SOURCES_GAME_IMPL_GENGINE_H_ */
