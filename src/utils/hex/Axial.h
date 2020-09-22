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
/// \file   Position.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 22 septembre 2020, 21:12
///

#ifndef POSITION_H
#define POSITION_H

#include <functional>
#include "utils/math/Math.h"
#include "utils/math/Vector.h"

namespace hex {
  
  struct Axial : public math::Vector<float> {
    
    Axial();
    Axial(const float & x, const float & y);
    Axial(const math::Vector<float> & v);
    
    /// \brief Call given function on this tile and each adjacent ones
    ///   this function stops after first tile on which func return true
    ///   or after tested all 7 tiles
    /// System of position passed to callback is the same as curent system
    void mapNeightbours(const std::function<bool(const Axial &)> & func) const;
    
    /// \brief Return position rounded to tile's center
    Axial tile() const;
    
    /// \brief Return vector major orientation between 0 and 5 (incl)
    ///   with 0 on bottom's verticle and turning counter-clockwise
    int orientation() const;
    
    struct TileHasher {
      std::size_t operator() (const Axial & v) const;
    };

    struct TileEquals {
      bool operator() (const Axial & u, const Axial & v) const;
    };
  };
}

#endif /* POSITION_H */

