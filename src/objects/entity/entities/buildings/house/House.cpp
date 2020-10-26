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
/// \file   House.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 22 septembre 2020, 09:18
///

#include "House.h"
#include "objects/decorator/decorators/drawable/Helpers.h"
    
namespace {
  bool isStorageType(const std::type_info& type) noexcept {
    return typeid(decorators::Inventory) == type
        || typeid(decorators::Storage) == type;
  }
}

core::Pointer 
House::doFindDecorator(const std::type_info& type) noexcept {
  if (isStorageType(type)) {
    return _storage;
  }
  else {
    return core::Pointer(nullptr);
  }
}
const core::Pointer 
House::doFindDecorator(const std::type_info& type) const noexcept {
  if (isStorageType(type)) {
    return _storage;
  }
  else {
    return core::Pointer(nullptr);
  }
}

House::Builder::Builder(const world::Position& pos) noexcept :
  Entity::Builder(pos, decorators::WorldObject::Size::Tile)
{
}

void House::Builder::operator() (core::Pointer& ptr) noexcept {
  this->Entity::Builder::operator() (ptr);
  House& house(static_cast<House&>(*ptr));
  /* create the storage */
  decorators::Storage::Builder builder(ptr, {
    Stack(Stack::Ressource::Wood, 0, 100),
    Stack(Stack::Ressource::Rock, 0, 50)
  });
  house._storage = core::IAllocator::Get().createObject(
      typeid(decorators::Storage), builder);
  /* create the render target */
  decorators::ADrawable::Builder dwbuild(ptr);
  house._drawable = core::IAllocator::Get().createObject(
    typeid(decorators::CDrawable<House>), dwbuild);
  decorators::DrawableHelpers::bindDrawableToWorldObject(
    house._position, house._drawable);
}