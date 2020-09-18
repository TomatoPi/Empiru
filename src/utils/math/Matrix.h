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
/// \file   Matrix.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 10 septembre 2020, 23:48
///

#ifndef MATRIX_H
#define MATRIX_H

/// \brief 2x2 Matrix class with :
///   M = |a b|
///       |c d|
struct Matrix22 {
  
  float _a; ///< a
  float _b; ///< b
  float _c; ///< c
  float _d; ///< d
  
  /// \brief Basic constructor
  Matrix22(float a, float b, float c, float d);
  
  /// \brief Matrix multiplication
  Matrix22 operator* (const Matrix22 & b) const;
  
  /// \brief Inverse Matrix
  /// \pre Matrix must be inversible
  Matrix22 inverse() const;

  /// \brief Turn in unitary Matrix (with det = 1)
  /// \pre Matrix must be inversible
  Matrix22 unit() const;
  
  /// \brief Return matrix's determinant
  float det() const;
};

#endif /* MATRIX_H */
