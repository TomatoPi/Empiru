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
#include "utils/world/WorldPtr.h"
#include "utils/world/Allocator.h"

/// \brief Concrete implementation of Allocators using STL vectors
template <class T>
class WorldAllocator : public Allocator<WorldObject,WorldPtr> {
private:
  
  typedef std::vector<T>        Container; ///< Array of objects
  typedef std::vector<WorldPtr> RefTable;  ///< Array of references
  
  Container _objects; ///< Array of objects
  RefTable  _rtable;  ///< Array of references
  
public:
  
  /// \brief Constructor
  WorldAllocator() : _objects(), _rtable() {}
    
  /// \brief Must create one instance of associated object and return it.
  /// This allocator is the only object's owner, and user should never
  ///   delete them himself.
  /// Refecrences returned must be stable (always represent the same object)
  /// \warning not thread safe
  virtual WorldPtr createObject() {
    assert(_objects.size() == _rtable.size());
    std::size_t idx(_objects.size());
    WorldPtr ptr(*this, idx);
    _objects.emplace_back();
    _rtable.emplace_back(ptr);
    assert(_objects.size() == _rtable.size());
    return ptr;
  }
  
  /// \brief Must free obj and dealocate associated memory.
  /// Must be the only way used to destroy objects.
  /// The strategy used for dealocation is swap ersaed obj and last obj,
  ///   reducing reference update count to one or zero
  virtual void deleteObject(const WorldPtr & ref) {
    assert(ref.isValid());
    assert(_objects.size() == _rtable.size());
    std::size_t erased(ref._ref->_idx), swapped(_objects.size() -1);
    // Swap last and erased elements then update associated reference
    if (1 < _objects.size() && erased != swapped) {
      _rtable[swapped]._ref->_idx = erased;
      std::swap(_objects[erased], _objects[swapped]);
      std::swap(_rtable[erased], _rtable[swapped]);
    }
    // destroy last object and associated reference
    _rtable.back().deprecate();
    _objects.pop_back();
    _rtable.pop_back();
    assert(_objects.size() == _rtable.size());
  }
  
  virtual WorldObject & operator[] (std::size_t idx) {
    return _objects[idx];
  }
  virtual const WorldObject & operator[] (std::size_t idx) const {
    return _objects[idx];
  }
  
  /// \brief Must call given callback on each object
  ///   Callback parameters are the object and the associated reference
  /// \warning Delete objects inside the callback may cause miss
  virtual void foreach(std::function<void(WorldObject &, WorldPtr)> func)
  {
    assert(_objects.size() == _rtable.size());
    for (std::size_t i(0) ; i<_objects.size() ; ++i) {
      func(_objects[i], _rtable[i]);
    }
    assert(_objects.size() == _rtable.size());
  }
};

#endif /* GENERICALLOCATOR_H */
