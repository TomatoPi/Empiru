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
/// \file   Decorator.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 8 octobre 2020, 23:13
///

#ifndef DECORATOR_H
#define DECORATOR_H

#include "core/Object.h"

/// \brief namespace containing all decorator related stuff
class Decorator : public core::Object {
protected:  
  
  core::Pointer _entity;
  
public:

  Decorator() noexcept = default;
  virtual ~Decorator() noexcept = default;
  
  /// \brief By default decorators are not callables
  virtual bool operator() () noexcept override {assert(0);}
  
  const core::Pointer& entity() const noexcept {return _entity;}
  
  /// \brief Generally decorators are passive objects that do not react events
  virtual void doOnNotify(const core::Pointer&, const core::Object::Event&) 
  noexcept override
  {}

  struct Builder : public core::Object::Builder {
    core::Pointer _entity;
    Builder() noexcept : core::Object::Builder(), _entity(nullptr) {}
    virtual void operator() (core::Pointer& ptr) noexcept override {
      this->core::Object::Builder::operator() (ptr);
      Decorator& deco(static_cast<Decorator&>(*ptr));
      deco._entity = _entity;
    }
  };
};

#endif /* DECORATOR_H */

