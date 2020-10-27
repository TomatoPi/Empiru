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
/// \file   NewAllocator.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 21 octobre 2020, 21:48
///
#ifndef NEWALLOCATOR_H
#define NEWALLOCATOR_H

#include "../Handle.h"
#include "../Pointer.h"

#include <utility>
#include <cassert>
#include <type_traits>

namespace alloc {

/// \brief Concrete implementation of Handle wraping on standard pointer
///   Useful to provide compatibility between standard raw pointers
///   and this SmartPointer library
/// This Handle provide make_shared like feature
template<class T, class U>
class WrapHandle : public AHandle<U> {
public:

  /// \brief Create the handle to instanciate associated object
  template<typename ...Args>
  explicit WrapHandle(Args &&...args) noexcept :
      AHandle<U>(), _obj(std::forward<Args>(args)...) {
    static_assert(std::is_base_of<U,T>::value, "T must be derived from U");
  }
  /// \brief No more needed
  virtual ~WrapHandle() noexcept = default;

  /// \brief Prevent missuse
  WrapHandle(const WrapHandle&) = delete;
  WrapHandle& operator=(const WrapHandle&) = delete;
  WrapHandle(WrapHandle&&) = delete;
  WrapHandle& operator =(WrapHandle&&) = delete;

  U* asPtr() noexcept override {
    return &_obj;
  }
  const U* asPtr() const noexcept override {
    return &_obj;
  }
  U& asRef() noexcept override {
    return _obj;
  }
  const U& asRef() const noexcept override {
    return _obj;
  }

private:

  T _obj;
};
}

#endif /* NEWALLOCATOR_H */

