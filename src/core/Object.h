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
#include <set>

/// \brief Namespace of core features
namespace core {
  
  /// \brief Base class of all dynamic objects used in the game and engine
  ///   A version of Observer design pattern is embeded within this class
  ///   Because all objects are finely related using a event system
  ///   They all are Observers and Subjects at the same time
  class Object {
  //////////////////////////////////////////////////////////////////////////
  protected:
    
    /// \brief Polymorphic base class for object events
    class Event {public: virtual ~Event() noexcept = default;};
    /// \brief Object launched when an 
    class EventObjectDestroyed : public Event {};
    
  public:
    
    /// \brief Functor class used to Contruct an Object
    class Builder {
    public:
      Builder() noexcept = default;
      virtual void operator() (Pointer& ptr) noexcept {
        ptr->_this = ptr;
      }
    };
    
  //////////////////////////////////////////////////////////////////////////
  private:
    
    std::set<Pointer,alloc::PtrComp> _observers; ///< List of observers
    
  protected:

    Pointer _this;      ///< Might be very useful
    
  //////////////////////////////////////////////////////////////////////////  
  public:

    Object() noexcept = default;
    virtual ~Object() noexcept = default;
    
    Pointer ptr() noexcept { return _this; }
    
    /// \brief Some objects are callables
    virtual void operator() () noexcept = 0;
    
    /// \brief Method to call when an object is beeing destroyed
    void discard() noexcept {
      notify(EventObjectDestroyed());
    }
    
    /// \brief Method used to subscribe to this object events
    void subscribe(const core::Pointer& ptr) noexcept {
      assert(ptr != _this && "Object must not subcribe itself");
      _observers.emplace(ptr);
    }
    /// \brief Method used to unsubscribe from this object events
    void unsubscribe(const core::Pointer& ptr) noexcept {
      assert(ptr != _this && "Object must not subcribe itself");
      _observers.erase(ptr);
    }

  protected:
    
    /// \brief Must be called on events
    virtual void 
    doOnNotify(const core::Pointer& p, const Event& e) noexcept = 0;
    
    /// \brief Callback called when an object has launched an event
    /// \param p : The object that lanched the event
    /// \param e : The event launched
    void onNotify(const core::Pointer& ptr, const Event& event) noexcept {
      // Object is detached to prevent constant polling of ptr corectness in
      // notify method
      if (typeid(event) == typeid(EventObjectDestroyed)) {
        unsubscribe(ptr);
      }
      doOnNotify(ptr, event);
    }
    
    /// \brief Method used by an object to alert it subscribers
    void notify(const Event& event) noexcept {
      for (auto object : _observers) {
        object->onNotify(_this, event);
      }
    }
  };
}

#endif /* GAME_ENGINE_OBJECT_H */