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
/// \file   Vectorial.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 22 septembre 2020, 19:28
///
#ifndef MATH_2D_VECTOR_H
#define MATH_2D_VECTOR_H

#include "Matrix.h"

#include <cmath>
#include <typeinfo>
#include <type_traits>
#include <ostream>

namespace math {

/// \brief 2D Vector class
template<typename T, class _Vect>
struct _Vector {

  T _x; ///< Horizontal or RightDown position
  T _y; ///< Vertical Position

  /// \brief Build the null vector
  _Vector() noexcept :
      _Vector(static_cast<T>(0), static_cast<T>(0)) {
  }
  /// \brief Build a vector with given components
  _Vector(T x, T y) noexcept :
      _x(x), _y(y) {
  }
  /// \brief Copy constructor
  _Vector(const _Vector &v) noexcept :
      _x(v._x), _y(v._y) {
  }

  static _Vect polar(T ro, T theta) noexcept {
    static_assert(std::is_floating_point<T>::value,
        "Require T beeing a non integral type");
    return _Vect(ro * std::cos(theta), ro * std::sin(theta));
  }

  /// \brief Conversion constructor
  template<typename F, class _VectF>
  explicit _Vector(const _Vector<F, _VectF> &v) noexcept :
      _x(static_cast<F>(v._x)), _y(static_cast<F>(v._y)) {
  }

  /// \brief Return true if all coordinates are equals
  bool operator==(const _Vect &v) const noexcept {
    return _x == v._x && _y == v._y;
  }
  /// \brief Return false if all coordinates are equals
  bool operator!=(const _Vect &v) const noexcept {
    return !(*this == v);
  }

  /// \brief Scale the vector by given factor
  template<typename F>
  _Vect operator*(F f) const noexcept {
    return _Vect(_x * f, _y * f);
  }
  /// \brief Scale the vector by given factor
  template<typename F>
  _Vect& operator*=(F f) noexcept {
    return *this = *this * f;
  }

  /// \brief Summ two vectors
  _Vect operator+(const _Vect &v) const noexcept {
    return _Vect(_x + v._x, _y + v._y);
  }
  /// \brief Summ two vectors
  _Vector& operator+=(const _Vect &v) noexcept {
    return *this = *this + v;
  }

  /// \brief Substract two vectors, return this - v
  _Vect operator-(const _Vect &v) const noexcept {
    return _Vect(_x - v._x, _y - v._y);
  }
  /// \brief Substract two vectors, return this - v
  _Vector& operator-=(const _Vect &v) noexcept {
    return *this = *this - v;
  }

  /// \brief Return the oposite vector
  _Vect operator-() const noexcept {
    return _Vect(-_x, -_y);
  }

  /// \brief Apply given transformation to this vector
  template<typename F>
  _Vect operator*(const Matrix22<F> &M) const noexcept {
    return _Vect(_x * M._a + _y * M._b, _x * M._c + _y * M._d);
  }
  /// \brief Apply given transformation to this vector
  template<typename F>
  _Vector& operator*=(const Matrix22<F> &M) const noexcept {
    return *this = *this * M;
  }

  /// \brief Return as unitary vector
  /// \warning Require T beeing an non integral type
  _Vect unit() const noexcept {
    static_assert(std::is_floating_point<T>::value,
        "Require T beeing a non integral type");
    T n(static_cast<T>(1) / norm());
    return _Vect(_x * n, _y * n);
  }
  /// \brief Normalize to unitatry vector
  _Vector& toUnit() noexcept {
    return *this = unit();
  }

  /// \brief Return vector's norm
  T norm() const noexcept {
    return std::hypot(_x, _y);
  }

  /// \brief Return distance between points a and b
  static T distance(const _Vect &a, const _Vect &b) noexcept {
    return (a - b).norm();
  }

  /// \brief Functor that define an order relation on vectors.
  /// sorting them by ascending Y
  struct AscYCompare {
    bool operator()(const _Vect &u, const _Vect &v) noexcept {
      return u._y < v._y || (u._y == v._y && u._x < v._x);
    }
  };
};

template<typename T, class V>
std::ostream& operator<< (std::ostream& stream, const _Vector<T,V>& v) noexcept {
  return stream << "(" << v._x << "," << v._y << ")";
}

template<typename T>
struct Vector: public _Vector<T, Vector<T>> {
  Vector() noexcept :
      math::_Vector<T, Vector<T>>() {
  }
  Vector(T x, T y) noexcept :
      math::_Vector<T, Vector<T>>(x, y) {
  }
  Vector(const math::_Vector<T, Vector<T>> &v) noexcept :
      math::_Vector<T, Vector<T>>(v) {
  }
};
}

#endif /* MATH_2D_VECTOR_H */
