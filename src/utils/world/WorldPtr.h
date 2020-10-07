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
/// \file   WorldRef.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 19 septembre 2020, 06:14
///

#ifndef WORLDREF_H
#define WORLDREF_H

#include "utils/world/Allocator.h"
#include "utils/world/WorldObject.h"

///
/// \brief Object used to keep safe references on WorldObjects
///
/// Because of object's blind storage, pointers and references may not be safe
///   due to data reordering.
/// This handler must answer this problem by insure proper tracking of 
///   referenced objects.
///
/// Thus, this handler must be used every time a singular object would be tracked
///
class WorldPtr {
private:
  
  friend struct WorldPtrHash;   ///< Hasher on referenced object's anchor adress
  friend struct WorldPtrComp;   ///< Comparaison on anchors adresses
  friend struct WorldPtrEquals; ///< True if referenced objects are the same
  
  /// \brief Allow the concrete allocator to access Ptr's ref and real contructor
  template <class T> friend class WorldAllocator;
  /// \brief Alias for WorldAllocator
  typedef Allocator<WorldObject,WorldPtr> _Allocator;
  
  /// \brief Internal struct used to track an object in the allocator
  ///   A WorldPtr is a smart shared pointer to a WorldRef
  struct WorldRef {
    
    /// \brief Construct a smart ref on given allocator cell
    WorldRef(_Allocator& alloc, std::size_t idx) noexcept :
      _alloc(alloc), _idx(idx), _count(1), _valid(true)
    {
    }
    /// \brief Default destructor is enougth
    ~WorldRef() noexcept = default;
    
    /// \brief Prevent missuse
    WorldRef() = delete;
    /// \brief Prevent missuse
    WorldRef(const WorldRef&) = delete;
    /// \brief Prevent missuse
    WorldRef& operator= (const WorldRef&) = delete;
    /// \brief Prevent missuse
    WorldRef(WorldRef&&) = delete;
    /// \brief Prevent missuse
    WorldRef& operator =(WorldRef&&) = delete;
    
    _Allocator& _alloc;
    std::size_t _idx;
    std::size_t _count;
    bool        _valid;
  };
  
  WorldRef* _ref; ///< Pointer to the associated object's smart ref
  
  /// \brief Called to eventualy decrease and release owning on ref
  ///   if ref was not null and refcount drop to zero
  ///   ref is dealocated
  void releaseRef() noexcept {
    if (_ref) {
      _ref->_count -= 1;
      if (_ref->_count == 0) {
        delete _ref;
      }
    }
  }
  /// \brief Called to eventualy increase and take own on ref
  ///   if ref is not null, it's owner count is incremented
  void acquire(WorldRef *ref) noexcept {
    _ref = ref;
    if (_ref) {
      _ref->_count += 1;
    }
  }
  /// \brief Mark the associated object as no longer existing
  ///   After calling this function dereferencing this ptr is not allowed
  void deprecate() noexcept {
    if (_ref) {
      _ref->_valid = false;
    }
  }
  
  /// \brief The only way to create a valid ptr
  WorldPtr(_Allocator& alloc, std::size_t idx) noexcept :
      _ref(new WorldRef(alloc, idx))
  {
  }
  
public:
  /// \brief Create a nullptr
  explicit WorldPtr(std::nullptr_t) :
      _ref(nullptr)
  {
  }
  /// \brief Create a nullptr
  WorldPtr() noexcept : 
      _ref(nullptr) 
  {
  }
  /// \brief Copy a ptr and increase references count
  WorldPtr(const WorldPtr& ptr) noexcept : 
    _ref(ptr._ref)
  {
    acquire(ptr._ref);
  }
  /// \brief Copy assign a ptr and increase references count
  WorldPtr& operator= (const WorldPtr& ptr) noexcept {
    releaseRef();
    acquire(ptr._ref);
    return *this;
  }
  /// \brief Move construct a ptr, don't increase references count
  WorldPtr(WorldPtr&& ptr) noexcept :
    _ref(ptr._ref)
  {
    ptr._ref = nullptr;
  }
  /// \brief Move assing a ptr, relase current, don't increase newest
  WorldPtr& operator= (WorldPtr&& ptr) noexcept {
    releaseRef();
    _ref = ptr._ref;
    ptr._ref = nullptr;
    return *this;
  }
  ~WorldPtr() noexcept {
    releaseRef();
  }
  /// \brief Useful to release an object
  WorldPtr& operator= (std::nullptr_t) noexcept {
    releaseRef();
    _ref = nullptr;
    return *this;
  }

  /// \brief Must return a reference to the associated object
  WorldObject* operator-> () {
    assert(isValid() && "Dereferenced invalid WorldPtr");
    return &_ref->_alloc[_ref->_idx];
  }
  /// \brief Must return a reference to the associated object
  const WorldObject* operator-> () const {
    assert(isValid() && "Dereferenced invalid WorldPtr");
    return &_ref->_alloc[_ref->_idx];
  }

  /// \brief Must return a reference to the associated object
  WorldObject& operator* () {
    assert(isValid() && "Dereferenced invalid WorldPtr");
    return _ref->_alloc[_ref->_idx];
  }
  /// \brief Must return a reference to the associated object
  const WorldObject& operator* () const {
    assert(isValid() && "Dereferenced invalid WorldPtr");
    return _ref->_alloc[_ref->_idx];
  }

  /// \brief Must return true while the associated object exist
  ///   false otherwise
  bool isValid() const noexcept {
    return _ref && _ref->_valid;
  }
  /// \brief Must return true while the associated object exist
  ///   false otherwise
  operator bool() const noexcept {
    return isValid();
  }
  
  /// \brief Return true if referenced objects are the same
  bool operator== (const WorldPtr& b) {
    return _ref == b._ref;
  }
};

/// \brief Functor that hash a ptr according to it's referenced adress
struct WorldPtrHash {
  std::size_t operator() (const WorldPtr & ptr) const {
    return reinterpret_cast<std::size_t>(ptr._ref);
  }
};

/// \brief Functor that compare referenced objects adresses
struct WorldPtrComp {
  bool operator() (const WorldPtr & a, const WorldPtr & b) const {
    return a._ref < b._ref;
  }
};

/// \brief Functor that return true if referenced objects are the same
struct WorldPtrEquals {
  bool operator() (const WorldPtr & a, const WorldPtr & b) const {
    return a == b;
  }
};

#endif /* WORLDREF_H */
