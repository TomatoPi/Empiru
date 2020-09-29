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
/// \file   GenericAllocator.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 19 septembre 2020, 06:18
///

#ifndef GENERICALLOCATOR_H
#define GENERICALLOCATOR_H

#include <vector>
#include <cassert>
#include "utils/engine/Allocator.h"

/// \brief Generic implementation of Allocators using STL vectors
template <class T>
class GenericAllocator : public Allocator {
private:
  
  /// \brief Private implementation of WorldRef
  struct GWorldRef : public WorldRef {
    
    GenericAllocator & _alloc; ///< Container
    std::size_t        _idx;   ///< Refered object
    
    /// \brief Constructor
    GWorldRef(GenericAllocator & alloc, std::size_t idx) : 
      _alloc(alloc), _idx(idx) 
    {
    }
    /// \brief return referenced object
    virtual WorldObject & operator-> () {
      return _alloc._objects[_idx];
    }
    /// \brief return referenced object as immutable
    virtual const WorldObject & operator-> () const {
      return _alloc._objects[_idx];
    }
    /// \brief return referenced object
    virtual WorldObject & operator* () {
      return _alloc._objects[_idx];
    }
    /// \brief return referenced object as immutable
    virtual const WorldObject & operator* () const {
      return _alloc._objects[_idx];
    }
  };

  typedef std::vector<T>          Container; ///< Array of objects
  typedef std::vector<GWorldRef*> RefTable;  ///< Array of references
  
  Container _objects; ///< Array of objects
  RefTable  _rtable;  ///< Array of references
  
public:
  
  /// \brief Constructor
  GenericAllocator() : _objects(), _rtable() {}
    
  /// \brief Must create one instance of associated object and return it.
  /// This allocator is the only object's owner, and user should never
  ///   delete them himself.
  /// Refecrences returned must be stable (always represent the same object)
  /// \warning not thread safe
  virtual WorldRef * createObject() {
    assert(_objects.size() == _rtable.size());
    std::size_t idx(_objects.size());
    GWorldRef *ref(new GWorldRef(*this, idx));
    _objects.emplace_back();
    _rtable.emplace_back(ref);
    assert(_objects.size() == _rtable.size());
    return ref;
  }
  
  /// \brief Must free obj and dealocate associated memory.
  /// Must be the only way used to destroy objects.
  /// The strategy used for dealocation is swap ersaed obj and last obj,
  ///   reducing reference update count to one or zero
  virtual void deleteObject(WorldRef * r) {
    assert(_objects.size() == _rtable.size());
    GWorldRef *ref(static_cast<GWorldRef*>(r));
    std::size_t erased(ref->_idx), swapped(_objects.size() -1);
    // Swap last and erased elements then update associated reference
    if (1 < _objects.size() && erased != swapped) {
      _rtable[swapped]->_idx = erased;
      std::swap(_objects[erased], _objects[swapped]);
      std::swap(_rtable[erased], _rtable[swapped]);
    }
    // destroy last object and associated reference
    _objects.pop_back();
    _rtable.pop_back();
    delete ref;
    assert(_objects.size() == _rtable.size());
  }
  
  /// \brief Must call given callback on each object
  ///   Callback parameters are the object and the associated reference
  /// \warning Delete objects inside the callback may cause miss
  virtual void foreach(std::function<void(WorldObject & obj, WorldRef *)> func)
  {
    assert(_objects.size() == _rtable.size());
    for (std::size_t i(0) ; i<_objects.size() ; ++i) {
      func(_objects[i], _rtable[i]);
    }
    assert(_objects.size() == _rtable.size());
  }
};

#endif /* GENERICALLOCATOR_H */
