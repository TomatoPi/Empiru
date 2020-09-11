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
/// \file   Matrix.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 10 septembre 2020, 23:48
///

#include "Matrix.h"

Matrix22::Matrix22(float a, float b, float c, float d) :
  _a(a),
  _b(b),
  _c(c),
  _d(d)
{  
}

Matrix22 Matrix22::operator* (const Matrix22 & A) const {
  return Matrix22(
      _a * A._a + _b * A._c, _a * A._b + _b * A._d,
      _c * A._a + _d * A._c, _c * A._b + _d * A._d);
}