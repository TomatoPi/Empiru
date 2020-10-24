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
/// \file   Builder.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 24 octobre 2020, 00:46
///

#ifndef DECORATOR_BUILDER_H
#define DECORATOR_BUILDER_H

#include "core/Builder.h"

namespace {
  static void ownerDied(
    core::Pointer decorator, 
    const core::OSubject<core::Events::ObjectDestroyed>&, 
    const core::Events::ObjectDestroyed&)
  {
    decorator->discard();
  }
}

namespace Decorator {
  struct Builder : public core::Builder {
    core::Pointer _owner;
    
    Builder(const core::Pointer& ptr) noexcept : 
      core::Builder(), _owner(ptr) {}
    
    void operator() (core::Pointer& ptr) noexcept override {
      this->core::Builder::operator() (ptr);
      using std::placeholders::_1;
      using std::placeholders::_2;
      _owner->core::OSubject<core::Events::ObjectDestroyed>::addSubscriber(
        ptr, std::bind(ownerDied, ptr, _1, _2));
    }
  };
}

#endif /* DECORATOR_BUILDER_H */

