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
/// \file   Object.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 21 octobre 2020, 13:34
///

#ifndef GAME_ENGINE_OBJECT_H
#define GAME_ENGINE_OBJECT_H

#include "Pointer.h"
#include "Observer.h"

/// \brief Namespace of core features
namespace core {
  
  namespace Events {
    class ObjectDestroyed {};
  }
  
  /// \brief Base class of all dynamic objects used in the game and engine
  ///   A version of Observer design pattern is embeded within this class
  ///   Because all objects are finely related using a event system
  ///   They all are Observers and Subjects at the same time
  class Object : public OSubject<Events::ObjectDestroyed> {
  protected:

    friend class Builder;
    Pointer _this;      ///< Might be very useful
    
  public:

    Object() noexcept = default;
    virtual ~Object() noexcept = default;
    
    Pointer ptr() noexcept { return _this; }
    
    template <typename T>
    T& as() noexcept {
      return static_cast<T&>(*this);
    }
    
    template <typename T>
    const T& as() const noexcept {
      return static_cast<const T&>(*this);
    }
    
    /// \brief Some objects are callables, this callback must return true while
    ///  the object is alive, when it return false, object will be destroyed
    /// \return True while the object is alive
    virtual bool update() noexcept = 0;
    
    /// \brief Method to call to suicide an object
    void discard() noexcept {
      OSubject<Events::ObjectDestroyed>::notify();
    }
  };
  
  template <typename EventT>
  auto sudoCommitSuicide(core::Pointer object) {
    auto func = [](core::Pointer decorator, 
      const core::OSubject<EventT>&, 
      const EventT&)
      -> void {
        decorator->discard();
      };
    return SuperObserver::bindCallback(func, object);
  }
}

#endif /* GAME_ENGINE_OBJECT_H */