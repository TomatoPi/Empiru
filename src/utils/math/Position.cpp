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
/// \file   Position.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 18 septembre 2020, 09:09
/// \brief Provide utils for 2D carthesian coordinates
///

#include "Position.h"

/// \brief Integeer 2D coordinates
Position::Position(int x, int y) : _x(x), _y(y) {
  
}

/// \brief Functor that return true if a.y is smaller than b.y 
///   or y' are equals and x' smaller
/// Useful to use Position as Key in ordered containers
///   Resulting an ascending sort on Y coordinate
bool PosCompareAscY::operator() (
  const Position & a, const Position & b) 
const {
  return a._y < b._y || (a._y == b._y && a._x < b._x);
}
