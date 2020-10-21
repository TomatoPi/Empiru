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
/// \file   Behaviour.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 20 octobre 2020, 09:07
///

#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include "engine/core/decorator/Decorator.h"

namespace decorators {
  
  class Behaviour : public Decorator {
  public:
    
    Behaviour() noexcept = default;
    virtual ~Behaviour() noexcept = default;
    
    virtual void update() noexcept = 0;
    
    class Builder : public Decorator::Builder {
    public:
      
      explicit Builder(const Pointer& entity) noexcept : 
        Decorator::Builder(entity) {}
      
      virtual void operator() (Pointer& ptr) const noexcept {
        this->Decorator::Builder::operator ()(ptr);
        this->addMarkers(ptr, typeid(Behaviour));
      }
    };
  };
}

#endif /* BEHAVIOUR_H */
