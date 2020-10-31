/*
 * Copyright (C) 2020 tomato
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
/// \file   EUID.cpp
/// \author tomato
///
/// \date 30 oct. 2020 20:58:11
///
#include "EUID.h"

namespace game {

std::ostream& operator<< (std::ostream& s, const EUID& a) noexcept {
  return s << a.val;
}
bool operator<(const EUID &a, const EUID &b) noexcept {
  return a.val < b.val;
}
bool operator==(const EUID &a, const EUID &b) noexcept {
  return a.val == b.val;
}

}
