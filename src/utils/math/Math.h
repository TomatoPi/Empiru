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
/// \file   Math.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 12 septembre 2020, 06:41
///

#ifndef MATH_H
#define MATH_H

namespace math {
  
  /// \brief Uniform rounding function that push halfvalues toward +inf
  ///
  ///   Default 'round' function in std push half values away from 0
  ///   but this behaviour leads to difference on negatives or positives
  ///   -0.5 and 0.5 will be rounded to -1 and 1 (resp) witch may cause
  ///   problems
  ///
  ///   This function will round -0.5 and 0.5 to 0 and 1 (resp)
  ///   which may be more stable for several operations
  int mrnd(float a);
}

#endif /* MATH_H */
