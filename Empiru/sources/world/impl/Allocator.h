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
/// \file   Allocator.h
/// \author tomato
///
/// \date 27 oct. 2020 13:28:53
///
#ifndef SOURCES_WORLD_IMPL_ALLOCATOR_H_
#define SOURCES_WORLD_IMPL_ALLOCATOR_H_

#include <alloc/impl/IndexAllocator.h>
#include "world/IAllocator.h"

namespace world {
namespace impl {
class Allocator final : public IAllocator {
private:

  using _Allocator = alloc::IndexAllocator<Object, Object>;
  _Allocator _alloc;

public:
  Allocator() noexcept = default;
  virtual ~Allocator() noexcept = default;

  Object::Pointer createObject(Object::Size s, const Position &p, float r,
      int o) override;

  void destroyObject(Object::Pointer ptr) override;
};
} /* namespace impl */
} /* namespace world */

#endif /* SOURCES_WORLD_IMPL_ALLOCATOR_H_ */
