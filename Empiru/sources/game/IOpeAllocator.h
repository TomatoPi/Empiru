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
/// \file   IDecoAllocator.h
/// \author tomato
///
/// \date 28 oct. 2020 16:41:31
///
#ifndef SOURCES_GAME_IOPEALLOCATOR_H_
#define SOURCES_GAME_IOPEALLOCATOR_H_

#include "Operator.h"
#include <functional>

namespace game {

class IOpeAllocator {
private:
  static IOpeAllocator *_allocator;
public:

  static void registerAllocator(IOpeAllocator *a) noexcept {
    _allocator = a;
  }

  static IOpeAllocator& Get() noexcept {
    return *_allocator;
  }

  virtual ~IOpeAllocator() noexcept = default;

  virtual Operator::Pointer createObject(const OUID, Operator::Builder&) = 0;

  virtual void destroyGarbadge() = 0;

  virtual void addCreationSubscriber(const OUID,
      std::function<void(Operator::Pointer ptr)>&&) noexcept = 0;
  virtual void addDestructionSubscriber(const OUID,
      std::function<void(Operator::Pointer ptr)>&&) noexcept = 0;
};

}  // namespace game

#endif /* SOURCES_GAME_IOPEALLOCATOR_H_ */
