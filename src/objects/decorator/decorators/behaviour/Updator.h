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
/// \file   Updator.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 20 octobre 2020, 09:20
///

#ifndef DECORATOR_BEHAVIOUR_UPDATOR_H
#define DECORATOR_BEHAVIOUR_UPDATOR_H

#include "engine/core/decorator/DecoratorUpdator.h"
#include "Behaviour.h"

namespace decorators {
  
  class BehaviourUpdator {
  public:
    virtual void 
    operator() (Decorator& deco, Pointer ptr) noexcept {
      static_cast<Behaviour&>(deco).update();
    }
  };
}

#endif /* DECORATOR_BEHAVIOUR_UPDATOR_H */

