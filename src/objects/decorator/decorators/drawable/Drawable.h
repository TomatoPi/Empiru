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
/// \file   Drawable.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 25 octobre 2020, 14:51
///

#ifndef DRAWABLE_DECORATOR_H
#define DRAWABLE_DECORATOR_H

#include "core/Object.h"
#include "world/core/Types.h"
#include "gui/core/Types.h"
#include "objects/decorator/Builder.h"

namespace decorators {
  
  namespace DrawableEvents {
    struct WorldPosMoved {};
  }
  
  class Drawable : 
    public core::Object, 
    public core::OSubject<DrawableEvents::WorldPosMoved> 
  {
  private:
    world::Position _worldpos;
    gui::Pixel      _viewpos;
    int _orientation;
  public:
    
    const gui::Pixel& viewpos() const noexcept {
      return _viewpos;
    }
    void viewpos(const gui::Pixel& p) noexcept {
      _viewpos = p;
    }
    
    int orientation() const noexcept {
      return _orientation;
    }
    void orientation(int o) noexcept {
      _orientation = o;
    }
    
    const world::Position& worldpos() const noexcept {
      return _worldpos;
    }
    void worldpos(const world::Position& p) noexcept {
      _worldpos = p;
      core::OSubject<DrawableEvents::WorldPosMoved>::notify();
    }
    
    bool update() noexcept override { assert(0); }
    
    struct Builder : public Decorator::Builder {
      Builder(const core::Pointer& ptr) noexcept : Decorator::Builder(ptr) {}
      void operator() (core::Pointer& ptr) noexcept override {
        this->core::Builder::operator() (ptr);
      }
    };
  };
}

#endif /* DRAWABLE_DECORATOR_H */

