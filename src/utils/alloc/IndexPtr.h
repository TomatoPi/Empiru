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
/// \file   IndexPtr.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 8 octobre 2020, 15:08
///

#ifndef INDEXPTR_H
#define INDEXPTR_H

#include <cassert>
#include "utils/alloc/Allocator.h"
#include "utils/alloc/Pointer.h"

namespace alloc {

  template <class Object>
  class IndexPtr : public SmartPointer<Object> {
  private:

    typedef Allocator<Object,IndexPtr<Object>,std::size_t> _Allocator;
    template <class T,class U> friend class IndexAllocator;

    class IndexHandle : public SmartPointer<Object>::Handle {
    public:
      
      /// \brief Construct a smart ref on given allocator cell
      IndexHandle(_Allocator& alloc, std::size_t idx) noexcept :
        SmartPointer<Object>::Handle(),
        _alloc(alloc), _idx(idx)
      {
      }
      /// \brief Default destructor is enougth
      virtual ~IndexHandle() noexcept = default;

      /// \brief Prevent missuse
      IndexHandle() = delete;
      /// \brief Prevent missuse
      IndexHandle(const IndexHandle&) = delete;
      /// \brief Prevent missuse
      IndexHandle& operator= (const IndexHandle&) = delete;
      /// \brief Prevent missuse
      IndexHandle(IndexHandle&&) = delete;
      /// \brief Prevent missuse
      IndexHandle& operator =(IndexHandle&&) = delete;

      virtual Object* asPtr() noexcept override {
        return &_alloc[_idx];
      }
      virtual const Object* asPtr() const noexcept override {
        return &_alloc[_idx];
      }
      virtual Object& asRef() noexcept override {
        return _alloc[_idx];
      }
      virtual const Object& asRef() const noexcept override {
        return _alloc[_idx];
      }

      _Allocator& _alloc; ///< The associated container
      std::size_t _idx;   ///< Index of the object in the container
    };


    /// \brief Change the referenced object's index inside the container
    void update(std::size_t idx) noexcept {
      IndexHandle* ref(
        static_cast<IndexHandle*>(SmartPointer<Object>::getRef()));
      assert(ref);
      ref->_idx = idx;
    }

    /// \brief Return the current storage index
    std::size_t index() const noexcept {
      const IndexHandle* ref(
        static_cast<const IndexHandle*>(SmartPointer<Object>::getRef()));
      assert(ref);
      return ref->_idx;
    }

    /// \brief Construct a valid pointer
    IndexPtr(_Allocator& alloc, std::size_t idx) noexcept :
      SmartPointer<Object>(new IndexHandle(alloc, idx))
    {
    }

  public:

    /// \brief Create a nullptr
    IndexPtr() noexcept : SmartPointer<Object>(nullptr) {}
    /// \brief Create a nullptr
    explicit IndexPtr(std::nullptr_t) noexcept : SmartPointer<Object>(nullptr) {}
    /// \brief Useful to release an object
    IndexPtr& operator= (std::nullptr_t) noexcept {
      this->SmartPointer<Object>::operator= (nullptr);
      return *this;
    }
  };
}

#endif /* INDEXPTR_H */

