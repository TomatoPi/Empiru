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
/// \date 27 oct. 2020 17:55:21
///
#ifndef SOURCES_RENDER_IALLOCATOR_H_
#define SOURCES_RENDER_IALLOCATOR_H_

#include "ATarget.h"

namespace render {

namespace Events {
struct TargetCreated {
  ATarget::Pointer ptr;
  TargetCreated(const ATarget::Pointer &ptr) noexcept :
      ptr(ptr) {
  }
};
} /* namespace Events */

class IAllocator: public SuperObserver::Subject< // @suppress("Invalid template argument")
    IAllocator, Events::TargetCreated> {
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

  virtual ATarget::Pointer createObject(AssetUID,
      ATarget::Builder&) = 0;

  virtual void destroyGarbadge() = 0;
};

} /* namespace render */

#endif /* SOURCES_RENDER_IALLOCATOR_H_ */
