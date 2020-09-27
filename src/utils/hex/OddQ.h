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
/// \file   OddQ.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 22 septembre 2020, 22:33
///

#ifndef HEX_ODDQ_COORDS_H
#define HEX_ODDQ_COORDS_H

#include "utils/math/Vector.h"

namespace hex {
 
  struct OddQ : public math::Vector<float> {
    
    OddQ() noexcept : 
      math::Vector<float>() 
    {
    }
    OddQ(float x, float y) noexcept : 
      math::Vector<float>(x,y) 
    {
    }
    OddQ(const math::Vector<float> & v) noexcept : 
      math::Vector<float>(v) 
    {
    }
    
  };
}

#endif /* HEX_ODDQ_COORDS_H */

