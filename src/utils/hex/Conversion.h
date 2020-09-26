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
/// \file   Conversion.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 22 septembre 2020, 22:28
///

#ifndef CONVERSION_H
#define CONVERSION_H
#pragma once

#include "OddQ.h"
#include "Axial.h"
#include "Grid.h"

namespace hex {
  
  inline OddQ toOddQ(const Axial & v) {
    return OddQ(
      v._x, 
      v._y + (v._x - (math::fastmrnd(v._x) & 1)) / 2.);
  }
  
  inline Axial toAxial(const OddQ & v) {
    return Axial(
      v._x, 
      v._y - (v._x - (math::fastmrnd(v._x) & 1)) / 2.);
  }
  
  inline Axial toAxial(const Grid & v) {
    return Axial(
      v._x / 3., 
      v._y / 2. - v._x / 6.);
  }
  
  inline Grid toGrid(const Axial & v) {
    return Grid(
      v._x * 3, 
      v._y * 2 + v._x);
  }
}

#endif /* CONVERSION_H */

