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

#include <cassert>

namespace alloc {
  ///
  /// \brief Object used to keep safe references on Allocator's objects
  ///
  /// Because of object's blind storage, pointers and references may not be safe
  ///   due to data reordering.
  /// This handler must answer this problem by insure proper tracking of 
  ///   referenced objects.
  ///
  /// Thus, this handler must be used every time a singular object 
  ///   would be tracked
  ///
  template <class Object>
  class SmartPointer {
  protected:
    
    /* ******************************************************************** */
    /*                      Potentialy Harmfull methods                     */
    /* ******************************************************************** */

    /// \brief Internal struct used to track an object in the allocator
    class Handle {
    public:
      
      /// \brief Construct a smart ref on given allocator cell
      Handle() noexcept : _count(1), _valid(true) {}
      /// \brief Default destructor is enougth
      virtual ~Handle() noexcept = default;

      /// \brief Prevent missuse
      Handle(const Handle&) = delete;
      /// \brief Prevent missuse
      Handle& operator= (const Handle&) = delete;
      /// \brief Prevent missuse
      Handle(Handle&&) = delete;
      /// \brief Prevent missuse
      Handle& operator =(Handle&&) = delete;
      
      virtual Object* asPtr() noexcept = 0;
      virtual const Object* asPtr() const noexcept = 0;
      virtual Object& asRef() noexcept = 0;
      virtual const Object& asRef() const noexcept = 0;
      
    private:
      
      friend class SmartPointer;
      
      std::size_t _count; ///< Number of pointers that reference this handle
      bool        _valid; ///< True if the handle is valid
    };
    
    /// \brief Mark the associated object as no longer existing
    ///   After calling this function dereferencing this ptr is not allowed
    void deprecate() noexcept {
      assert(_ref && "Deprecating an invalid pointer");
      _ref->_valid = false;
    }
    
    /// \brief Create a Pointer from a constructed reference
    explicit SmartPointer(Handle* ref) noexcept : _ref(ref) {}
    
    /// \brief Used by the derived classes to retrieve the object's handle
    ///   but prevent free modification on stored handle
    Handle* getRef() noexcept {
      return _ref;
    }
    
    /// \brief Used by the derived classes to retrieve the object's handle
    ///   but prevent free modification on stored handle
    const Handle* getRef() const noexcept {
      return _ref;
    }
    
  private:
    
    /* ******************************************************************** */
    /*                       Reference count tracking                       */
    /* ******************************************************************** */

    friend struct PtrHash;   ///< Hasher on anchor's adress
    friend struct PtrComp;   ///< Comparaison on anchors adresses
    friend struct PtrEquals; ///< True if referenced objects are the same

    Handle* _ref; ///< Pointer to the associated object's smart ref

    /// \brief Called to eventualy decrease and release owning on ref
    ///   if ref was not null and refcount drop to zero
    ///   ref is dealocated
    void releaseRef() noexcept {
      if (_ref) {
        _ref->_count -= 1;
        if (_ref->_count == 0) {
          /* if the pointer was the last ref, but the object is always valid */
          /* it means that we're losing reference to an allocator's object */
          /* and the we're discarding ptr without explicit release of memory */
          assert(!_ref->_valid && "Memory Leaked !!");
          delete _ref;
        }
      }
    }
    /// \brief Called to eventualy increase and take own on ref
    ///   if ref is not null, it's owner count is incremented
    void acquire(Handle *ref) noexcept {
      _ref = ref;
      if (_ref) {
        _ref->_count += 1;
      }
    }

  public:
    
    /* ******************************************************************** */
    /*                              General Methods                         */
    /* ******************************************************************** */
    
    /// \brief Create a nullptr
    explicit SmartPointer(std::nullptr_t) :
        _ref(nullptr)
    {
    }
    /// \brief Create a nullptr
    SmartPointer() noexcept : 
        _ref(nullptr) 
    {
    }
    /// \brief Copy a ptr and increase references count
    SmartPointer(const SmartPointer& ptr) noexcept : 
      _ref(ptr._ref)
    {
      acquire(ptr._ref);
    }
    /// \brief Copy assign a ptr and increase references count
    SmartPointer& operator= (const SmartPointer& ptr) noexcept {
      releaseRef();
      acquire(ptr._ref);
      return *this;
    }
    /// \brief Move construct a ptr, don't increase references count
    SmartPointer(SmartPointer&& ptr) noexcept :
      _ref(ptr._ref)
    {
      ptr._ref = nullptr;
    }
    /// \brief Move assing a ptr, relase current, don't increase newest
    SmartPointer& operator= (SmartPointer&& ptr) noexcept {
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
    SmartPointer& operator= (std::nullptr_t) noexcept {
      releaseRef();
      _ref = nullptr;
      return *this;
    }

    /// \brief Must return a reference to the associated object
    Object* operator-> () {
      assert(isValid() && "Dereferenced invalid Pointer");
      return _ref->asPtr();
    }
    /// \brief Must return a reference to the associated object
    const Object* operator-> () const {
      assert(isValid() && "Dereferenced invalid Pointer");
      return _ref->asPtr();
    }

    /// \brief Must return a reference to the associated object
    Object& operator* () {
      assert(isValid() && "Dereferenced invalid Pointer");
      return _ref->asRef();
    }
    /// \brief Must return a reference to the associated object
    const Object& operator* () const {
      assert(isValid() && "Dereferenced invalid Pointer");
      return _ref->asRef();
    }

    /// \brief Must return true if the pointer can be safely dereferenced
    bool isValid() const noexcept {
      return _ref && _ref->_valid;
    }
    /// \brief Must return true if the pointer used to reference a valid object
    ///   but the object has been destroyed
    bool isDeprecated() const noexcept {
      return _ref && !_ref->_valid;
    }
    
    /// \brief Must return true if the pointer can be dereferenced
    explicit operator bool() const noexcept {
      return isValid();
    }

    /// \brief Return true if referenced objects are the same
    bool operator== (const SmartPointer& b) const noexcept {
      return _ref == b._ref;
    }
    
    bool operator!= (const SmartPointer& b) const noexcept {
      return _ref != b._ref;
    }
  };

  /// \brief Functor that hash a ptr according to it's referenced adress
  struct PtrHash {
    template <class Object>
    std::size_t operator() (const SmartPointer<Object>& ptr) 
      const noexcept
    {
      return reinterpret_cast<std::size_t>(ptr._ref);
    }
  };

  /// \brief Functor that compare referenced objects adresses
  struct PtrComp {
    template <class Object>
    bool operator() (const SmartPointer<Object>& a, const SmartPointer<Object>& b) 
      const noexcept 
    {
      return a._ref < b._ref;
    }
  };

  /// \brief Functor that return true if referenced objects are the same
  struct PtrEquals {
    template <class Object>
    bool operator() (const SmartPointer<Object>& a, const SmartPointer<Object>& b) 
      const noexcept
    {
      return a._ref == b._ref;
    }
  };
}

#endif /* POINTER_H */

