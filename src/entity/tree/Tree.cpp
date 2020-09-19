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
/// \file   Tree.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 17 septembre 2020, 08:45
/// \brief Tree WorldObject declaration
///

#include "Tree.h"

/// \brief Constructor
Tree::Tree() : WorldObject(FlatHexPosition(), 0.1), _size(100) {
  
}

/// \brief return quantity of wood in this tree
int Tree::size() const {
  return _size;
}
/// \brief try to remove 'qty' wood from the tree
/// \return quantity removed
int Tree::reduce(int qty) {
  return _size -= std::min(qty, _size);
}