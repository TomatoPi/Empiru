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

#include <vector>
#include <cassert>
#include "utils/core/IndexPtr.h"
#include "utils/core/Allocator.h"

namespace core {

  /// \brief Concrete implementation of Allocators using STL vectors
  /// T is the concrete type of stored objects
  /// U is the superclass used to handle stored objects
  template <class T, class U>
  class IndexAllocator : public Allocator<U,IndexPtr<U>,std::size_t> {
  private:

    typedef IndexPtr<U>           _Pointer;   ///< Associated Smart pointer
    typedef std::vector<T>        _Container; ///< Array of objects
    typedef std::vector<_Pointer> _RefTable;  ///< Array of references

    _Container _objects; ///< Array of objects
    _RefTable  _rtable;  ///< Array of references

  public:

    /// \brief Constructor
    IndexAllocator() : _objects(), _rtable() {}

    /// \brief Must create one instance of associated object and return it.
    /// This allocator is the only object's owner, and user should never
    ///   delete them himself.
    /// Refecrences returned must be stable (always represent the same object)
    /// \warning not thread safe
    virtual _Pointer createObject() override {
      assert(_objects.size() == _rtable.size());
      std::size_t idx(_objects.size());
      _Pointer ptr(*this, idx);
      _objects.emplace_back();
      _rtable.emplace_back(ptr);
      assert(_objects.size() == _rtable.size());
      return ptr;
    }

    /// \brief Must free obj and dealocate associated memory.
    /// Must be the only way used to destroy objects.
    /// The strategy used for dealocation is swap ersaed obj and last obj,
    ///   reducing reference update count to one or zero
    virtual void deleteObject(const _Pointer& ref) override {
      assert(ref.isValid());
      assert(_objects.size() == _rtable.size());
      std::size_t erased(ref.index()), swapped(_objects.size() -1);
      // Swap last and erased elements then update associated reference
      if (1 < _objects.size() && erased != swapped) {
        _rtable[swapped].update(erased);
        std::swap(_objects[erased], _objects[swapped]);
        std::swap(_rtable[erased], _rtable[swapped]);
      }
      // destroy last object and associated reference
      _rtable.back().deprecate();
      _objects.pop_back();
      _rtable.pop_back();
      assert(_objects.size() == _rtable.size());
    }

    virtual U& operator[] (const std::size_t& idx) override {
      return _objects[idx];
    }
    virtual const U& operator[] (const std::size_t& idx) const override {
      return _objects[idx];
    }

    /// \brief Must call given callback on each object
    ///   Callback parameters are the object and the associated reference
    /// \warning Delete objects inside the callback may cause miss
    virtual void foreach(std::function<void(U&, _Pointer)> func) override
    {
      assert(_objects.size() == _rtable.size());
      for (std::size_t i(0) ; i<_objects.size() ; ++i) {
        func(_objects[i], _rtable[i]);
      }
      assert(_objects.size() == _rtable.size());
    }
  };
}

#endif /* INDEXALLOCATOR_H */
