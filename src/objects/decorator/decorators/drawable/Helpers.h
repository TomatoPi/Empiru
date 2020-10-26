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
/// \file   Helpers.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 25 octobre 2020, 20:56
///

#ifndef HELPERS_H
#define HELPERS_H

#include "Drawable.h"
#include "objects/decorator/decorators/worldobj/WorldObject.h"

namespace decorators {
  namespace DrawableHelpers {
    
    auto WorldPosMovedCallback(const core::Pointer& ptr) noexcept;
    
    auto WorldPosRotatedCallback(const core::Pointer& ptr) noexcept;
    
    void bindDrawableToWorldObject(
      core::Pointer& optr, 
      const core::Pointer& dptr) 
    noexcept;
  }
}

#endif /* HELPERS_H */

