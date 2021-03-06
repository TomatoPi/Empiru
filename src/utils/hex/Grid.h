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
/// \file   Grid.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 22 septembre 2020, 22:30
///

#ifndef HEX_GRID_COORDS_H
#define HEX_GRID_COORDS_H

#include <functional>
#include "utils/math/Vector.h"

namespace hex {
  
  struct Grid : public math::_Vector<float,Grid> {
    
    Grid() noexcept : 
      math::_Vector<float,Grid>() 
    {
    }
    Grid(float x, float y) noexcept : 
      math::_Vector<float,Grid>(x,y) 
    {
    }
    explicit Grid(const math::_Vector<float,Grid>& v) noexcept : 
      math::_Vector<float,Grid>(v) 
    {
    }
    
    /// \brief Call given function on this tile and each adjacent ones
    ///   this function stops after first tile on which func return true
    ///   or after tested all 7 tiles
    /// System of position passed to callback is the same as curent system
    void mapNeightbours(const std::function<bool(const Grid &)> & func) 
      const noexcept
    {
      static float offsets[] = {0,0, 0,-2, 3,-1, 3,1, 0,2, -3,1, -3,-1};
      for (size_t i(0) ; i<14 ; i+=2) {
        if (func(Grid(_x + offsets[i], _y + offsets[i+1]))) {
          break;
        }
      }
    }
  };
}

#endif /* HEX_GRID_COORDS_H */

