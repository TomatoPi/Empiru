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
/// \file   IndexAllocator.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 8 octobre 2020, 15:12
///
#ifndef INDEXALLOCATOR_H
#define INDEXALLOCATOR_H

#include "../Handle.h"
#include "../Pointer.h"
#include "../Allocator.h"

#include <list>
#include <vector>
#include <cassert>

namespace alloc {

/// \brief Concrete implementation of Allocators using STL vectors
/// T is the concrete type of stored objects
/// U is the superclass used to handle stored objects
template<class T, class U>
class IndexAllocator: public IAllocator<U, SmartPointer<U>> {
private:

  using _Container = std::vector<T>; ///< Array of objects

  class IndexHandle final : public AHandle<U> {
  public:

    /// \brief Construct a smart ref on given allocator cell
    IndexHandle(_Container &array, std::size_t idx) noexcept :
        AHandle<U>(), _array(array), _idx(idx) {
    }
    /// \brief Default destructor is enougth
    virtual ~IndexHandle() noexcept final = default;

    /// \brief Prevent missuse
    IndexHandle() = delete;
    /// \brief Prevent missuse
    IndexHandle(const IndexHandle&) = delete;
    /// \brief Prevent missuse
    IndexHandle& operator=(const IndexHandle&) = delete;
    /// \brief Prevent missuse
    IndexHandle(IndexHandle&&) = delete;
    /// \brief Prevent missuse
    IndexHandle& operator =(IndexHandle&&) = delete;

    U* asPtr() noexcept override final {
      return &_array[_idx];
    }
    const U* asPtr() const noexcept override final {
      return &_array[_idx];
    }
    U& asRef() noexcept override final {
      return _array[_idx];
    }
    const U& asRef() const noexcept override final {
      return _array[_idx];
    }

    _Container &_array; ///< The associated container
    std::size_t _idx;   ///< Index of the object in the container
  };

  using _Pointer = SmartPointer<U>;       ///< Associated Smart pointer
  using _RefTable = std::vector<_Pointer>; ///< References

  _Container _objects; ///< Array of objects
  _RefTable _rtable;  ///< Array of references

public:

  /// \brief Constructor
  IndexAllocator() :
      _objects(), _rtable() {
  }
  virtual ~IndexAllocator() noexcept {
    for (auto ptr : _rtable) {
      ptr.handle().deprecate();
    }
  }

  /// \brief Must create one instance of associated object and return it.
  /// This allocator is the only object's owner, and user should never
  ///   delete them himself.
  /// Refecrences returned must be stable (always represent the same object)
  /// \warning not thread safe
  _Pointer createObject() override {
    assert(_objects.size() == _rtable.size());
    std::size_t idx(_objects.size());
    _Pointer ptr(new IndexHandle(_objects, idx));
    _objects.emplace_back(ptr);
    _rtable.emplace_back(ptr);
    assert(_objects.size() == _rtable.size());
    return ptr;
  }

  /// \brief Must free obj and dealocate associated memory.
  /// Must be the only way used to destroy objects.
  /// The strategy used for dealocation is swap ersaed obj and last obj,
  ///   reducing reference update count to one or zero
  void deleteObject(_Pointer ptr) override {
    assert(ptr.isValid());
    assert(_objects.size() == _rtable.size());
    std::size_t erased(static_cast<IndexHandle&>(ptr.handle())._idx);
    std::size_t swapped(_objects.size() - 1);
    // Swap last and erased elements then update associated reference
    if (1 < _objects.size() && erased != swapped) {
      static_cast<IndexHandle&>(_rtable[swapped].handle())._idx = erased;
      std::swap(_objects[erased], _objects[swapped]);
      std::swap(_rtable[erased], _rtable[swapped]);
    }
    // destroy last object and associated reference
    _rtable.back().handle().deprecate();
    _objects.pop_back();
    _rtable.pop_back();
    assert(_objects.size() == _rtable.size());
  }

  /// \brief Must call given callback on each object
  ///   Callback parameters are the object and the associated reference
  /// \warning Delete objects inside the callback may cause miss
  void foreach(std::function<void(U&)> func) override final {
    assert(_objects.size() == _rtable.size());
    for (auto &obj : _objects) {
      func(obj);
    }
    assert(_objects.size() == _rtable.size());
  }
};
}

#endif /* INDEXALLOCATOR_H */
