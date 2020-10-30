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
/// \file   StackHelpers.h
/// \author tomato
///
/// \date 29 oct. 2020 20:23:28
///
#ifndef SOURCES_ITEMS_STACKHELPERS_H_
#define SOURCES_ITEMS_STACKHELPERS_H_

#include "Stack.h"

namespace items {

namespace helpers {

struct StackTypeLess {
  bool operator()(const Stack &a, const Stack &b) const noexcept {
    return a.type() < b.type();
  }
};

struct StackTypeEquals {
  bool operator()(const Stack &a, const Stack &b) const noexcept {
    return a.type() == b.type();
  }
};

struct StackTypeHash {
  std::size_t operator()(const Stack &a) const noexcept {
    return std::hash<Ressource>()(a.type());
  }
};
}  // namespace helpers

}  // namespace items

#endif /* SOURCES_ITEMS_STACKHELPERS_H_ */
