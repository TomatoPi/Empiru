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

#ifndef VECTORIAL_H
#define VECTORIAL_H

#include <cmath>
#include "Matrix.h"

namespace math {
  
  /// \brief 2D Vector class
  template <typename T>
  struct Vector {
    T _x; ///< Horizontal or RightDown position
    T _y; ///< Vertical Position
    
    /// \brief Build the null vector
    Vector() : Vector(static_cast<T>(0), static_cast<T>(0)) {
    }
    /// \brief Build a vector with given components
    Vector(const T & x, const T & y) : _x(x), _y(y) {
    }
    /// \brief Copy constructor
    template <typename F>
    Vector(const Vector<F> & v) : 
      _x(static_cast<F>(v._x)), _y(static_cast<F>(v._y))
    {
    }
    
    /// \brief Return true if all coordinates are equals
    bool operator== (const Vector & v) const {
      return _x == v._x && _y == v._y;
    }
    /// \brief Return false if all coordinates are equals
    bool operator!= (const Vector & v) const {
      return ! (*this == v);
    }
    
    /// \brief Scale the vector by given factor
    template <typename F>
    Vector operator* (const F & f) const {
      return Vector(_x * f, _y * f);
    }
    /// \brief Scale the vector by given factor
    template <typename F>
    Vector & operator*= (const F & f) {
      return *this = *this * f;
    }
    
    /// \brief Summ two vectors
    Vector operator+ (const Vector & v) const {
      return Vector(_x + v._x, _y + v._y);
    }
    /// \brief Summ two vectors
    Vector & operator+= (const Vector & v) {
      return *this = *this + v;
    }
    
    /// \brief Substract two vectors, return this - v
    Vector operator- (const Vector & v) const {
      return Vector(_x - v._x, _y - v._y);
    }
    /// \brief Substract two vectors, return this - v
    Vector & operator-= (const Vector & v) {
      return *this = *this - v;
    }
    
    /// \brief Return the oposite vector
    Vector operator- () const {
      return Vector(-_x, -_y);
    }
    
    /// \brief Apply given transformation to this vector
    template <typename F>
    Vector operator* (const Matrix22<F> & M) const {
      return Vector(_x * M._a + _y * M._b, _x * M._c + _y * M._d);
    }
    /// \brief Apply given transformation to this vector
    template <typename F>
    Vector & operator*= (const Matrix22<F> & M) const {
      return *this = *this * M;
    }
    
    /// \brief Return as unitary vector
    Vector unit() const {
      T n(static_cast<T>(1) / norm());
      return Vector(_x * n, _y * n);
    }
    /// \brief Normalize to unitatry vector
    Vector & toUnit() {
      return *this = unit();
    }
    
    /// \brief Return vector's norm
    T norm() const {
      return std::hypot(_x, _y);
    }
    
    /// \brief Return distance between points a and b
    static T distance(const Vector & a, const Vector & b) {
      return (a - b).norm();
    }
    
    /// \brief Functor that define an order relation on vectors.
    /// sorting them by ascending Y
    struct AscYCompare {
      bool operator() (const Vector & u, const Vector & v) {
        return u._y < v._y || (u._y == v._y && u._x < v._x);
      }
    };
  };
}

#endif /* VECTORIAL_H */
