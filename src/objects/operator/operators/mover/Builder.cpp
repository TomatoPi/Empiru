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
/// \file   Builder.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 24 octobre 2020, 12:16
///

#include "Builder.h"
#include "Mover.h"

namespace operators {
  
  MoverBuilder::MoverBuilder(
    IWorldMap* worldMap,
    const core::Pointer& object, 
    float speed) 
  noexcept :
    _worldMap(worldMap),
    _object(object),
    _speed(speed)
  {  
  }

  void MoverBuilder::operator() (core::Pointer& ptr) noexcept {
    this->Operator::Builder::operator() (ptr);
    Mover& mover(static_cast<Mover&>(*ptr));
    mover._worldMap = _worldMap;
    mover._object = _object;
    mover._speed = _speed;
    /* Attach this mover to the object */
    _object->core::OSubject<core::Events::ObjectDestroyed>::addSubscriber(
      ptr, core::sudoCommitSuicide<core::Events::ObjectDestroyed>(ptr));
  }
}