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
/// \file   Allocator.cpp
/// \author tomato
///
/// \date 27 oct. 2020 13:28:53
///
#include "Allocator.h"

namespace world {

IAllocator *IAllocator::_allocator = nullptr;

namespace impl {

Object::Pointer Allocator::createObject(Object::Size s, const Position &p,
    float r, int o) {
  Object::Pointer ptr(_alloc.createObject());
  ptr->build(s, p, r, o);
  Subject<Events::ObjectCreated>::notify(ptr); // @suppress("Function cannot be resolved")
  return ptr;
}

void Allocator::destroyObject(Object::Pointer ptr) {
  _alloc.deleteObject(ptr);
}

} /* namespace impl */
} /* namespace world */
