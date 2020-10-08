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
/// \file   Allocator.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 19 septembre 2020, 05:09
/// \brief Interface for worldobjects allocator/container
///

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <functional>

namespace core {

  /// \brief Interface for worldobjects allocator/container
  ///   All objects of the same kind are sweeped on each game tick
  ///   So allocator should be aware of cache issues and data continuity
  template <class Base, class Ptr, typename Key>
  class Allocator {
  public:

    /// \brief Must create one instance of associated object and return it.
    /// This allocator is the only object's owner, and user should never
    ///   delete them himself.
    /// Refecrences returned must be stable (always represent the same object)
    virtual Ptr createObject() = 0;

    /// \brief Must free obj and dealocate associated memory.
    /// Must be the only way used to destroy objects
    virtual void deleteObject(const Ptr& ptr) = 0;

    virtual Base& operator[] (const Key&) = 0;
    virtual const Base& operator[] (const Key&) const = 0;

    /// \brief Must call given callback on each object
    ///   Callback parameters are the object and the associated reference
    /// \warning Delete objects inside the callback may cause undefined behaviour
    virtual void foreach(std::function<void(Base& obj, Ptr)> func) = 0;
  };
}
#endif /* ALLOCATOR_H */

