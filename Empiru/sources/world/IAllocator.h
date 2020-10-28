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
/// \file   IWorldAllocator.h
/// \author tomato
///
/// \date 27 oct. 2020 13:07:54
///
#ifndef SOURCES_WORLD_IALLOCATOR_H_
#define SOURCES_WORLD_IALLOCATOR_H_

#include "Object.h"
#include <observer/SuperObserver.h>

namespace world {

namespace Events {
struct ObjectCreated {
  Object::Pointer ptr;
  ObjectCreated(const Object::Pointer &ptr) noexcept :
      ptr(ptr) {
  }
};
}

class IAllocator: public SuperObserver::Subject< // @suppress("Invalid template argument")
    IAllocator, Events::ObjectCreated> {
private:
  static IAllocator *_allocator;
public:

  template<typename E>
  using Subject = SuperObserver::Subject<IAllocator, E>; // @suppress("Invalid template argument")

  static void registerAllocator(IAllocator *a) noexcept {
    _allocator = a;
  }

  static IAllocator& Get() noexcept {
    return *_allocator;
  }

  virtual ~IAllocator() noexcept = default;

  virtual Object::Pointer createObject(game::EUID, Object::Size,
      const Position&, float, int) = 0;

  virtual void destroyGarbage() noexcept = 0;
};
}

#endif /* SOURCES_WORLD_IALLOCATOR_H_ */
