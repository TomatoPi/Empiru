/*
 * Copyright (C) 2020 tomato
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
/// \file   IAllocator.h
/// \author tomato
///
/// \date 29 oct. 2020 16:23:18
///
#ifndef SOURCES_GAME_IALLOCATOR_H_
#define SOURCES_GAME_IALLOCATOR_H_

#include <observer/SuperObserver.h>
#include <functional>

namespace game {

template<typename T, typename DiscardE>
class IAllocator: public SuperObserver::Subject<IAllocator<T, DiscardE>, // @suppress("Invalid template argument")
    DiscardE> {
private:
  static IAllocator *_allocator;
public:

  template<typename E>
  using Subject = SuperObserver::Subject<IAllocator<T,DiscardE>, E>; // @suppress("Invalid template argument")

  static void registerAllocator(IAllocator *a) noexcept {
    _allocator = a;
  }

  static IAllocator& Get() noexcept {
    return *_allocator;
  }

  virtual ~IAllocator() noexcept = default;

  virtual typename T::Pointer createObject(typename T::Builder&) = 0;

  virtual void destroyGarbadge() = 0;

  virtual void addCreationSubscriber(const typename T::Kind,
      std::function<void(typename T::Pointer ptr)>&&) noexcept = 0;
  virtual void addDestructionSubscriber(const typename T::Kind,
      std::function<void(typename T::Pointer ptr)>&&) noexcept = 0;
};

template<typename T, typename E>
IAllocator<T, E> *IAllocator<T, E>::_allocator = nullptr;

} /* namespace game */

#endif /* SOURCES_GAME_IALLOCATOR_H_ */
