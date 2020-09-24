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
/// \file   HexConsts.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 17 septembre 2020, 14:07
///

#ifndef HEXCONSTS_H
#define HEXCONSTS_H

#include "utils/math/Matrix.h"

namespace hex {
  
  typedef math::Matrix22<float> Matrix;
  
  static const Matrix Identity(1, 0, 0, 1);
  
  /// \brief Clockwise 90° Axial Coordinate rotation Matrix
  static const Matrix RMatrix_C90A = Matrix(-0.5, -1, 1.25, 0.5).unit();
  /// \brief CounterClockwise 90° Axial Coordinate rotation Matrix
  static const Matrix RMatrix_CC90A = Matrix(0.5, 1, -1.25, -0.5).unit();
  
  /// \brief Clockwise 60° Axial Coordinate rotation Matrix
  static const Matrix RMatrix_C60A(0, -1, 1, 1);
  /// \brief CounterClockwise 60° Axial Coordinate rotation Matrix
  static const Matrix RMatrix_CC60A(1, 1, -1, 0);
  
}

#endif /* HEXCONSTS_H */

