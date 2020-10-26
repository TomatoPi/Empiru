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
/// \file   EngineInterface.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 02:11
///

#ifndef ENGINEINTERFACE_H
#define ENGINEINTERFACE_H

#include <functional>
#include <typeinfo>

#include "Pointer.h"
#include "Object.h"
#include "Builder.h"

namespace core {
  /// \brief Game Main Allocator, this interface must be used to create and
  ///   destroy dynamic game objects
  class IAllocator {
  private:

    /// \brief Singleloton
    static IAllocator *_instance;

  public:

    /// \brief Can only be called once
    static void RegisterInstance(IAllocator* i) noexcept {
      assert(_instance == nullptr && "Instance Already Registered ...");
      _instance = i;
    }

    /// \brief Return the allocator instance
    static IAllocator& Get() noexcept {
      return *_instance;
    }

    /// \brief Must be called to create a new game object
    virtual Pointer createObject(const std::type_info&, Builder&) noexcept = 0;

    /// \brief Must be called to destroy an object
    virtual void discardObject(core::Pointer ptr) noexcept = 0;
    
    using CreationObs = std::function<void(Pointer ptr)>;
    using DestructionObs = std::function<void(Pointer ptr)>;
    
    void addCreationSubscriber(const std::type_info&, const CreationObs&);
    void addDestructionSubscriber(const std::type_info&, const DestructionObs&);
  };
}

#endif /* ENGINEINTERFACE_H */

