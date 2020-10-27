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
/// \file   Handle.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 21 octobre 2020, 20:01
///
#ifndef HANDLE_H
#define HANDLE_H

#include <cassert>

namespace alloc {

/// \brief Object used as an anchor to a stored object
///   Keep an everytime up-to-date link between pointers and collection
///   Handles also keep track on count of pointers referencing it
///   used to keep pointers pseudo-valid when object is destroyed
/// Allocators MUST provide the associated handle in order to make SmartPointers
///   smart
template<class Object>
class AHandle {
public:

  /// \brief Construct a smart ref on given allocator cell
  AHandle() noexcept :
      _count(1), _valid(true) {
  }
  /// \brief Default destructor is enougth
  virtual ~AHandle() noexcept = default;

  /// \brief Prevent missuse
  AHandle(const AHandle&) = delete;
  AHandle& operator=(const AHandle&) = delete;
  AHandle(AHandle&&) = delete;
  AHandle& operator =(AHandle&&) = delete;

  virtual Object* asPtr() noexcept = 0;
  virtual const Object* asPtr() const noexcept = 0;
  virtual Object& asRef() noexcept = 0;
  virtual const Object& asRef() const noexcept = 0;

  /// \brief Mark the associated object as no longer existing
  ///   After called this function dereferencing this ptr is not allowed
  void deprecate() noexcept {
    _valid = false;
  }
  /// \brief Return true if associated object has been destroyed
  bool isDeprecated() const noexcept {
    return !_valid;
  }

  /// \brief Method to be called when a new pointer use this handle
  void aquire() noexcept {
    assert(0 < _count);
    _count += 1;
  }
  /// \brief Method to be called when a pointer no longer use this handle
  void release() noexcept {
    assert(0 < _count);
    _count -= 1;
  }
  /// \brief Return true if no more pointers use this handle
  bool hasNoMoreHolders() const noexcept {
    return _count <= 0;
  }

private:

  std::size_t _count; ///< Number of pointers that reference this handle
  bool _valid; ///< True if the handle is valid
};
}

#endif /* HANDLE_H */

