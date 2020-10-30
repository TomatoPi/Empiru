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
/// \file   Pointer.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 8 octobre 2020, 15:13
///
#ifndef POINTER_H
#define POINTER_H

#include "Handle.h"

#include <cassert>
#include <functional>
#include <type_traits>

namespace alloc {
///
/// \brief Object used to keep safe references on Allocator's objects
///
/// Because of object's blind storage, pointers and references may not be safe
///   due to data reordering.
/// This handler must answer this problem by insure proper tracking of
///   referenced objects.
/// Theremore, this pointer is always safe, and can allow to detect the case
///   where referenced object has been deleted, contrary to raw pointers
///
/// Thus, this handler must be used every time a singular object
///   would be tracked
///
template<class Object>
class SmartPointer {
private:

  /* ******************************************************************** */
  /*                       Reference count tracking                       */
  /* ******************************************************************** */

  using _Handle = AHandle<Object>;
  friend struct PtrHash;   ///< Hasher on anchor's adress
  friend struct PtrComp;   ///< Comparaison on anchors adresses
  friend struct PtrEquals; ///< True if referenced objects are the same

  _Handle *_ref; ///< Pointer to the associated object's smart ref

  /// \brief Called to eventualy decrease and release owning on ref
  ///   if ref was not null and refcount drop to zero
  ///   ref is dealocated
  void releaseRef() noexcept {
    if (_ref) {
      _ref->release();
      if (_ref->hasNoMoreHolders()) {
        /* if the pointer was the last ref, but the object is always valid */
        /* it means that we're losing reference to an allocator's object */
        /* and the we're discarding ptr without explicit release of memory */
        assert(_ref->isDeprecated() && "Memory Leaked !!");
        delete _ref;
      }
    }
  }
  /// \brief Called to eventualy increase and take own on ref
  ///   if ref is not null, it's owner count is incremented
  void acquire(_Handle *ref) noexcept {
    _ref = ref;
    if (_ref) {
      _ref->aquire();
    }
  }

public:

  /* ******************************************************************** */
  /*                              General Methods                         */
  /* ******************************************************************** */

  /// \brief Create a Pointer from a constructed Hanle
  explicit SmartPointer(_Handle *ref) noexcept :
      _ref(ref) {
  }
  /// \brief Create a nullptr
  SmartPointer(std::nullptr_t) noexcept :
      _ref(nullptr) {
  }
  /// \brief Create a nullptr
  SmartPointer() noexcept :
      _ref(nullptr) {
  }
  /// \brief Copy a ptr and increase references count
  SmartPointer(const SmartPointer &ptr) noexcept :
      _ref(ptr._ref) {
    acquire(ptr._ref);
  }
  /// \brief Copy assign a ptr and increase references count
  SmartPointer& operator=(const SmartPointer &ptr) noexcept {
    releaseRef();
    acquire(ptr._ref);
    return *this;
  }
  /// \brief Move construct a ptr, don't increase references count
  SmartPointer(SmartPointer &&ptr) noexcept :
      _ref(ptr._ref) {
    ptr._ref = nullptr;
  }
  /// \brief Move assing a ptr, relase current, don't increase newest
  SmartPointer& operator=(SmartPointer &&ptr) noexcept {
    releaseRef();
    _ref = ptr._ref;
    ptr._ref = nullptr;
    return *this;
  }
  /// \brief Release the handle
  ~SmartPointer() noexcept {
    releaseRef();
  }
  /// \brief Useful to release an object
  SmartPointer& operator=(std::nullptr_t) noexcept {
    releaseRef();
    _ref = nullptr;
    return *this;
  }

  /// \brief Must return a reference to the associated object
  Object* operator->() {
    assert(isValid() && "Dereferenced invalid Pointer");
    return _ref->asPtr();
  }
  /// \brief Must return a reference to the associated object
  const Object* operator->() const {
    assert(isValid() && "Dereferenced invalid Pointer");
    return _ref->asPtr();
  }

  /// \brief Must return a reference to the associated object
  Object& operator*() {
    assert(isValid() && "Dereferenced invalid Pointer");
    return _ref->asRef();
  }
  /// \brief Must return a reference to the associated object
  const Object& operator*() const {
    assert(isValid() && "Dereferenced invalid Pointer");
    return _ref->asRef();
  }

  /// \brief Must return true if the pointer can be safely dereferenced
  bool isValid() const noexcept {
    return _ref && !_ref->isDeprecated();
  }
  /// \brief Must return true if the pointer used to reference a valid object
  ///   but the object has been destroyed
  bool isDeprecated() const noexcept {
    return _ref && _ref->isDeprecated;
  }

  /// \brief MUST NEVER BE USED UNLESS YOU ARE AN ALLOCATOR
  /// \warning DO NOT USE
  _Handle& handle() noexcept {
    assert(_ref && "Getting handle of Invalid Ptr");
    return *_ref;
  }

  /// \brief Must return true if the pointer can be dereferenced
  explicit operator bool() const noexcept {
    return isValid();
  }

  /// \brief Return true if referenced objects are the same
  template<class U> friend bool
  operator==(const SmartPointer<U> &a, const SmartPointer<U> &b) noexcept;
  /// \brief Return true if referenced objects are not the same
  template<class U> friend bool
  operator!=(const SmartPointer<U> &a, const SmartPointer<U> &b) noexcept;
};

/// \brief Return true if referenced objects are the same
template<class U> bool operator==(const SmartPointer<U> &a,
    const SmartPointer<U> &b) noexcept {
  return a._ref == b._ref;
}
/// \brief Return true if referenced objects are not the same
template<class U> bool operator!=(const SmartPointer<U> &a,
    const SmartPointer<U> &b) noexcept {
  return a._ref != b._ref;
}

/// \brief Functor that hash a ptr according to it's referenced adress
struct PtrHash {
  template<class Object>
  constexpr std::size_t operator()(
      const SmartPointer<Object> &ptr) const noexcept {
    return reinterpret_cast<std::size_t>(ptr._ref);
  }
};

/// \brief Functor that compare referenced objects adresses
struct PtrComp {
  template<class Object>
  constexpr bool operator()(const SmartPointer<Object> &a,
      const SmartPointer<Object> &b) const noexcept {
    return a._ref < b._ref;
  }
};

/// \brief Functor that return true if referenced objects are the same
struct PtrEquals {
  template<class Object>
  constexpr bool operator()(const SmartPointer<Object> &a,
      const SmartPointer<Object> &b) const noexcept {
    return a._ref == b._ref;
  }
};
} /* alloc */

template<typename T> struct std::hash<alloc::SmartPointer<T>> {
  constexpr std::size_t operator()(
      const alloc::SmartPointer<T> &ptr) const noexcept {
    return alloc::PtrHash()(ptr);
  }
};

template<typename T> struct std::equal_to<alloc::SmartPointer<T>> {
  constexpr bool operator()(const alloc::SmartPointer<T> &a,
      const alloc::SmartPointer<T> &b) const noexcept {
    return alloc::PtrEquals()(a, b);
  }
};

template<typename T> struct std::less<alloc::SmartPointer<T>> {
  constexpr bool operator()(const alloc::SmartPointer<T> &a,
      const alloc::SmartPointer<T> &b) const noexcept {
    return alloc::PtrComp()(a, b);
  }
};

#endif /* POINTER_H */

