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
/// \file   Decorator.h
/// \author tomato
///
/// \date 28 oct. 2020 12:41:52
///
#ifndef SOURCES_GAME_OPERATOR_H_
#define SOURCES_GAME_OPERATOR_H_

#include <alloc/Pointer.h>
#include <game/EUID.h>
#include <observer/SuperObserver.h>
#include <uid/huid.h>

namespace game {

namespace Events {
struct OperatorDiscarded {
};
}  // namespace Events

class Operator: public SuperObserver::Subject<Operator, // @suppress("Invalid template argument")
    Events::OperatorDiscarded> {
public:
  using HierarchyGen = uid::HierarchicalUID<std::uint16_t>;
  using Kind = HierarchyGen::HUID;
  using Pointer = alloc::SmartPointer<Operator>;
  template<typename E>
  using Subject = SuperObserver::Subject<Operator,E>; // @suppress("Invalid template argument")
private:
  Pointer _this;
  EUID _entity;
  Kind _kind;
public:
  Operator() noexcept = delete;
  virtual ~Operator() noexcept = default;
  Operator(const Pointer &ptr) noexcept :
      _this(ptr), _entity(), _kind() {
  }

  const Pointer& ptr() const noexcept {
    return _this;
  }
  const EUID entity() const noexcept {
    return _entity;
  }
  const Kind kind() const noexcept {
    return _kind;
  }

  void discard() noexcept {
    Subject<Events::OperatorDiscarded>::notify(); // @suppress("Function cannot be resolved")
  }

  template <typename T>
  T& as() noexcept {
    return static_cast<T&>(*this);
  }
  template <typename T>
  const T& as() const noexcept {
    return static_cast<const T&>(*this);
  }

  virtual void update() noexcept = 0;

  static HierarchyGen& Hierarchy() noexcept {
    static HierarchyGen _instance;
    return _instance;
  }

  struct Builder {
    EUID entity;
    Kind kind;
    virtual ~Builder() noexcept = default;
    virtual void operator()(Pointer &ptr) noexcept {
      ptr->_entity = entity;
      ptr->_kind = kind;
    }
  };
};

}  // namespace game

#endif /* SOURCES_GAME_OPERATOR_H_ */
