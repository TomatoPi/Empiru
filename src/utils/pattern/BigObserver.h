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
/// \file   Observer.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 26 septembre 2020, 21:30
///
/// \brief This file provide an implementation of the Observer design pattern
///   coupled with a simple Event Handling mechanism.
/// Class that might be observed must inherit Subject, then,
///   an arbitrary count of Observers can be attached to this Subject
///   A table of <EventType,Callback> is used in the observer to perform
///   O(1) dispatch of events with safe and fast type resolution at a cost
///   of several inderections
/// \todo This specialized implementation could be easyly generalized with
///   changing Subject to a template class and parameterising Observer type
///   Or using more polymorphism on the observer
///

#ifndef BIG_OBSERVER_H
#define BIG_OBSERVER_H

#include <vector>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <cassert>
#include <ctime>
#include <iomanip>
#include <iostream>

#include "utils/log.h"

/// \brief Amalgam of an Observer and an EventHandler.
/// These two components aren't splited because of the heavy need of event
///   handling mechanism in the Observer pattern
/// So, the observer can also be used as a simple event handler by direct
///  call of the handleEvent() method (with associated event registering ahead)
template <class Event>
class BigObserver {
private:

  /// \brief Base class used for storage
  class AbstractHandler {
  public:
    /// \brief Prevent compiler insults
    virtual ~AbstractHandler() noexcept = default;
    /// \brief Make object callable
    virtual void operator() (const Event & event) = 0;
  };
  
  /// \brief Template class used to resolve event types at compile time.
  /// EventT is the type of handled event
  /// EventFunctorT is the callback, we use a template to allow use of function
  ///   pointer or functor object
  template <typename EventT, typename EventFunctorT>
  class Handler : public AbstractHandler {
  private:
    EventFunctorT _functor; ///< The callback used to handle event
  public:
    /// \brief Construct an Handler
    Handler(const EventFunctorT & func) noexcept :
      _functor(func)
    {
    }
    /// \brief prevent compile insults
    virtual ~Handler() noexcept = default;
    /// \brief Call the callback and cast event to proper type
    virtual void operator() (const Event & event) {
      _functor(static_cast<const EventT &>(event));
    }
  };
  
  /// \brief Lookup table for event dispatch
  typedef std::unordered_map<std::type_index,AbstractHandler*> HandlersTable;
  HandlersTable _table; ///< The event callback table
  
public:
  
  /// \brief Constructor
  BigObserver() noexcept : 
    _table() 
  {
  }
  /// \brief delete all allocated handlers
  virtual ~BigObserver() noexcept {
    for (auto & itr : _table) {
      delete itr.second;
    }
  }
  
  /// \brief Method used to set the callback for given event
  /// This method use template to enable type resolution at compile time
  /// EventT is the type of associated event
  /// \warning A single event Type cannot be registered twice
  template <typename EventT, typename EventFunctorT>
  void registerEvent(const EventFunctorT & func) {
    static_assert(std::is_base_of<Event,EventT>::value, 
            "EventT must inherit from Event");
    //static_assert(std::is_invocable<EventFunctorT, void(EventT)>::value,
    //        "EventFunctorT must be callable on EventT");
    bool result(_table.emplace(
      typeid(EventT), 
      new Handler<EventT,EventFunctorT>(func)).second);
    assert(result);
  }
  
  /// \brief Method called when an event is launched by an observed subject.
  /// If the event has been registered, the proper callback is called
  /// otherwise, nothing happens
  void handleEvent(const Event & event) const {
    auto itr(_table.find(std::type_index(typeid(event))));
    if (itr != _table.end()) {
//      LOG_DEBUG("Handle known Event : %20s <- %20s\n", typeid(*this).name(), typeid(event).name());
      itr->second->operator()(event);
    } else {
//      LOG_DEBUG("Unkown event Kind  : %20s <- %20s\n", typeid(*this).name(), typeid(event).name());
    }
  }
};

/// \brief The Subject class for Observer design pattern
/// Simply store list of atatched Observers and call their handleEvent() method
///   when an event is launched
template <class Event>
class BigSubject {
private:
  
  using _Observer = BigObserver<Event>;
  
  /// \brief A List of Observers
  typedef std::vector<_Observer*> Watchers;
  Watchers _watchers; ///< List of attached watchers
  
public:
  
  virtual ~BigSubject() noexcept = default;
  
  /// \brief Attach an observer to this subject
  /// This observer will be notified on each subject update
  void attachObserver(_Observer* obs) noexcept {
    assert(obs != nullptr && "Observer cannot be null");
    _watchers.push_back(obs);
  }
  
protected:
  
  /// \brief Called to send event to attached observers
  void sendNotification(const Event & event) const {
//    std::time_t time(std::time(nullptr));
//    std::tm tm = *std::localtime(&time);
//    std::cout << "\n" << std::put_time(&tm, "%H %M %S") << std::endl;
//    LOG_DEBUG("Send Event : %20s -> %20s\n", typeid(*this).name(), typeid(event).name());
    int i(0);
    for (auto & observer : _watchers) {
      observer->handleEvent(event);
      ++i;
    }
//    LOG_DEBUG("%d Notifications have been sent\n\n", i);
  }
};

#endif /* BIG_OBSERVER_H */