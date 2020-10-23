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
/// \file   PeonSprite.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 23 octobre 2020, 13:30
///

#ifndef PEONSPRITE_H
#define PEONSPRITE_H

#include "objects/decorator/core/Decorator.h"

namespace peon {
  struct PeonSprite : public Decorator {
    SlowCounter _anim;
    SlowCounter _wanim;
    SlowCounter _notanim;
    bool        _select;
    
    PeonSprite() noexcept : 
      _anim(7,6), _wanim(6,6), _notanim(2,6), _select(false) 
    {
    }
    
    virtual bool operator() () noexcept override {
      _anim.tick();
      _wanim.tick();
      _notanim.tick();
      return true;
    }
    
    /// \brief Generally decorators are passive objects that do not react events
    virtual void doOnNotify(const core::Pointer&, const core::Object::Event&) 
    noexcept override {
      
    }
    
    struct Builder : public Decorator::Builder {
      Builder() noexcept : Decorator::Builder() {}
      virtual void operator() (core::Pointer& ptr) noexcept override {
        this->Decorator::Builder::operator() (ptr);
      }
    };
  };
}

#endif /* PEONSPRITE_H */

