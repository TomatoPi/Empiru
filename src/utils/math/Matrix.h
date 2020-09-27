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

#include <cmath>
#include <cassert>

namespace math {
  /// \brief 2x2 Matrix class with :
  ///   M = |a b|
  ///       |c d|
  template <typename T>
  struct Matrix22 {

    T _a; ///< a
    T _b; ///< b
    T _c; ///< c
    T _d; ///< d

    /// \brief Basic constructor
    Matrix22(const T & a, const T & b, const T & c, const T & d) noexcept :
      _a(a), _b(b), _c(c), _d(d)
    {

    }

    /// \brief Matrix multiplication
    Matrix22 operator* (const Matrix22 & A) const noexcept {
      return Matrix22(
        _a * A._a + _b * A._c, _a * A._b + _b * A._d,
        _c * A._a + _d * A._c, _c * A._b + _d * A._d);
    }
    /// \brief Matrix multiplication
    Matrix22 & operator*= (const Matrix22 & A) noexcept {
      return *this = *this * A;
    }

    /// \brief Inverse Matrix
    /// \pre Matrix must be inversible
    Matrix22 inverse() const noexcept {
      T d(det());
      assert(d != static_cast<T>(0));
      d = static_cast<T>(1) / d;
      return Matrix22(_d*d, -_b*d, -_c*d, _a*d);
    }

    /// \brief Turn in unitary Matrix (with det = 1)
    /// \pre Matrix must be inversible
    Matrix22 unit() const noexcept {
      T d(det());
      assert(d != static_cast<T>(0));
      d = static_cast<T>(1) / std::sqrt(d);
      return Matrix22(_a*d, _b*d, _c*d, _d*d);
    }

    /// \brief Return matrix's determinant
    T det() const noexcept {
      return _a * _d - _b * _c;
    }
  };
}

#endif /* MATRIX_H */
