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
/// \file   Axial.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 22 septembre 2020, 21:12
///

#ifndef HEX_AXIAL_COORDS_H
#define HEX_AXIAL_COORDS_H

#include <functional>
#include "utils/math/Math.h"
#include "utils/math/Vector.h"

namespace hex {
  
  struct Axial : public math::_Vector<float,Axial> {
    
    Axial() noexcept : 
      math::_Vector<float,Axial>() 
    {
    }
    Axial(float x, float y) noexcept : 
      math::_Vector<float,Axial>(x,y) 
    {
    }
    explicit Axial(const math::_Vector<float,Axial>& v) noexcept :
      math::_Vector<float,Axial>(v)
    {    
    }
    
    float norm() const noexcept {
      return std::sqrt(_x*_x + _y*_y + _x*_y);
    }
    
    /// \brief Call given function on this tile and each adjacent ones
    ///   this function stops after first tile on which func return true
    ///   or after tested all 7 tiles
    /// System of position passed to callback is the same as curent system
    void mapNeightbours(const std::function<bool(const Axial &)> & func) 
      const noexcept 
    {
      static float offsets[] = {0,0, 0,-1, 1,-1, 1,0, 0,1, -1,1, -1,0};
      for (size_t i(0) ; i<14 ; i+=2) {
        if (func(Axial(_x + offsets[i], _y + offsets[i+1]))) {
          break;
        }
      }
    }
    
    /// \brief Return position rounded to tile's center
    Axial tile() const noexcept {
      int x(math::fastmrnd(_x)), y(math::fastmrnd(_y));
      float xx = _x - x, yy = _y - y;
      float u = xx + 2*yy, v = 2*xx + yy, w = yy - xx;
      if (w < 0) {
        if (u < -1) {
          y--;
        } else if (v > 1) {
          x++;
        }
      } else {
        if (v < -1) {
          x--;
        } else if (u > 1) {
          y++;
        }
      }
      return Axial(x, y);
    }
    
    /// \brief Return vector major orientation between 0 and 5 (incl)
    ///   with 0 on bottom's verticle and turning counter-clockwise
    int orientation() const noexcept {
      float u = _x + 2*_y, v = 2*_x + _y, w = _y - _x;
      static int hexans[2][2][2] = {{{0, 11}, {5, 4}}, {{1, 2}, {16, 3}}};
      assert(hexans[w<0][v<0][u<0] < 6);
      return hexans[w<0][v<0][u<0];
    }
    
    /// \brief Functor that return a Hash of given position
    /// Two positions on the same tile will have the same hash
    struct TileHasher {
      std::size_t operator() (const Axial & v) const noexcept {
        Axial tile(v.tile());
        std::size_t x(static_cast<std::size_t>(tile._x));
        std::size_t y(static_cast<std::size_t>(tile._y));
        return x ^ ((y << 16) | (y >> (sizeof(size_t) * 8 - 16)));
      }
    };

    /// \brief Functor that return true if the positions are on the same tile
    struct TileEquals {
      bool operator() (const Axial & u, const Axial & v) const noexcept {
        return u.tile() == v.tile();
      }
    };
  };
}

#endif /* HEX_AXIAL_COORDS_H */

