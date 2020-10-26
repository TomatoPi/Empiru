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
/// \file   Helpers.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 25 octobre 2020, 21:02
///

#include "Helpers.h"

namespace decorators {
  namespace DrawableHelpers {
    
    auto WorldPosMovedCallback(const core::Pointer& ptr) noexcept {
      auto func = [] (
        core::Pointer drawptr, 
        const core::OSubject<decorators::WorldObjectEvents::Moved>&, 
        const decorators::WorldObjectEvents::Moved& event)
        -> void {
          ADrawable& draw(static_cast<ADrawable&>(*drawptr));
          draw.worldpos(event.newp);
          draw.core::OSubject<DrawableEvents::WorldPosMoved>::notify();
      };
      return SuperObserver::bindCallback(func, ptr);
    }
    
    auto WorldPosRotatedCallback(const core::Pointer& ptr) noexcept {
      auto func = [] (
        core::Pointer drawptr, 
        const core::OSubject<decorators::WorldObjectEvents::Rotated>&, 
        const decorators::WorldObjectEvents::Rotated& event)
        -> void {
          ADrawable& draw(static_cast<ADrawable&>(*drawptr));
          draw.orientation(event.newr);
      };
      return SuperObserver::bindCallback(func, ptr);
    }
    
    void bindDrawableToWorldObject(
      core::Pointer& optr, 
      const core::Pointer& dptr)
    noexcept {
      using WO = decorators::WorldObject;
      using WOMoved = decorators::WorldObjectEvents::Moved;
      using WORot = decorators::WorldObjectEvents::Rotated;
      WO& object(static_cast<WO&>(*optr));
      object.core::OSubject<WOMoved>::addSubscriber(dptr, 
          WorldPosMovedCallback(dptr));
      object.core::OSubject<WORot>::addSubscriber(dptr, 
          WorldPosRotatedCallback(dptr));
    }
  }
}