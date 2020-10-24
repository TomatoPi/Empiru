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
/// \file   SuperObserver.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 23 octobre 2020, 19:18
///
/// \brief Small, Compact, (Fast ??), and Elegant implementation of Observer
///   design pattern, providing Compile time (or Hard-Coded) Event Dispatch,
///   at the cost of a bit memory overhead (24 bytes per event kind),
///   and an increased compile time
///
/// Core of this implementation resides in use of a bit of metaprograming :
///   We are using variadic template and multiple inheritence to overload
///   the standard notify method for each kind of event launched
///
/// Flexibility is achieved for the Observer side using Functors, so there is
///   no need for them to Inherit from a specific class, we can bind a specific
///   method for each event Kind
///
/// For exemple : with events kinds E1, E2
///   one can create a subject launching E1 and E2 with : Subject<...,E1,E2>
///   and register some observers using subject.<E1>::addSubscriber(...)
///
/// The major bottleneck of this implementation is that we need to explicitly
///   know who will launch what kind of event, and the absence of a unique
///   Subject superclass or interface, but maybe it's not critical
/// Theremore, templates mean verbosity in type definitions...
///
/// Event class must define a boolean value 'has_args' used to determine if
///   event's callback need callargs, or not
///

#ifndef SUPEROBSERVER_H
#define SUPEROBSERVER_H

#include <functional>
#include <map>

/// \brief Library's namespace
namespace SuperObserver {
  
  /// \brief Main definition of a subject, that will inherit specialisation for
  ///   each event kind
  /// Key    : Type used to identify an Observer in the Observers Table
  /// EventT, E... : The event kinds launched by this subject
  template <typename Key, typename KeyComp, typename EventT, typename ...E>
  class Subject : 
    public Subject<Key,KeyComp,EventT>, 
    public Subject<Key,KeyComp,E...> 
  {
  };
  
  /// \brief Recursive Closure, Specialisation of a subject for One event Kind
  /// This specialised class will be duplicated in the subject for each event kind
  template <typename Key, typename KeyComp, typename EventT>
  class Subject<Key,KeyComp,EventT>
  {
  private:
    
    /// \brief Conveniant alias
    using Me = Subject<Key,KeyComp,EventT>;
    /// \brief Observer typedef
    /// Subject : Class used to handle the subject
    using Observer = std::function<void(const Me&, const EventT&)>;
    /// Observers table, we do not use an unordered map to save a bit of memory
    ///   considering that there would never be a great amount of observers
    /// It could be reduced to a simple vector if count is realy small and if
    ///   observers are not removed frequently...
    /// \todo benches and tests
    using Observers = std::map<Key,Observer,KeyComp>;
    
    /// The observers table
    Observers _observers;
    
  public:
    
    /// \brief The common notify method of the design pattern
    /// \param u : arguments used to construct required event
    template <typename ...U>
    void notify(U&& ...u) noexcept {
      EventT event(std::forward<U>(u)...);
      for (auto& pair : _observers) {
        pair.second(*this, event);
      }
    }
    
    /// \brief Add a subscriber to this event Kind
    /// \param key : subscriber's identifier
    /// \param obs : the subscriber
    void addSubscriber(const Key& key, const Observer& obs) {
      _observers.emplace(key, obs);
    }
    
    /// \brief Remove a subscriber from this kind
    /// \param key : subscriber's identifier
    void removeSubscriber(const Key& key) {
      _observers.erase(key);
    }
  };
}

#endif /* SUPEROBSERVER_H */

