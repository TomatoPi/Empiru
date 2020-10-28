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
#ifndef SOURCES_GAME_DECORATOR_H_
#define SOURCES_GAME_DECORATOR_H_

#include <alloc/Pointer.h>
#include <game/EUID.h>
#include <observer/SuperObserver.h>
#include <vector>

namespace game {

using DUID = std::size_t;

class DKind final {
public:
  /// \brief Singleton
  static DKind& Get() noexcept;
  /// \brief Create a new root KUID
  DUID newKind() noexcept;
  /// \brief Create a new KUID, derived from 'father'
  DUID newKind(DUID father) noexcept;
  /// \brief Return true if 'kind' is derived from 'base'
  /// O(n) complexity, with n the depth of derivation tree
  bool isKindOf(DUID base, DUID kind) noexcept;
  /// \brief Return list of types kind derives from
  std::vector<DUID> basesOf(DUID kind) noexcept;
private:
  DKind() noexcept = default;
  ~DKind() noexcept = default;
  std::vector<DUID> _fathers;
};

namespace Events {
struct DecoratorDiscarded {
};
}  // namespace Events

class Decorator: public SuperObserver::Subject<Decorator, // @suppress("Invalid template argument")
    Events::DecoratorDiscarded> {
public:
  using Pointer = alloc::SmartPointer<Decorator>;
  template<typename E>
  using Subject = SuperObserver::Subject<Decorator,E>; // @suppress("Invalid template argument")
private:
  Pointer _this;
  EUID _entity;
  DUID _kind;
public:
  Decorator() noexcept = delete;
  ~Decorator() noexcept = default;
  Decorator(const Pointer &ptr) noexcept :
      _this(ptr), _entity(), _kind() {
  }

  const Pointer& ptr() const noexcept {
    return _this;
  }
  const EUID entity() const noexcept {
    return _entity;
  }
  const DUID kind() const noexcept {
    return _kind;
  }

  void discard() noexcept {
    Subject<Events::DecoratorDiscarded>::notify(); // @suppress("Function cannot be resolved")
  }

  template <typename T>
  T& as() noexcept {
    return static_cast<T&>(*this);
  }
  template <typename T>
  const T& as() const noexcept {
    return static_cast<const T&>(*this);
  }

  struct Builder {
    EUID entity;
    DUID kind;
    virtual ~Builder() noexcept = default;
    virtual void operator()(Pointer &ptr) noexcept {
      ptr->_entity = entity;
      ptr->_kind = kind;
    }
  };
};

}  // namespace game

#endif /* SOURCES_GAME_DECORATOR_H_ */
