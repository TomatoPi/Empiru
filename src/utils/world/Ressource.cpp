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
/// \file   Ressource.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 21 septembre 2020, 19:30
///

#include "Ressource.h"
#include <algorithm>

/// \brief Default Constructor, build invalid ressource
Stack::Stack() : Stack(Invalid, 0) {
  
}
/// \brief Create a ressource of given type and size
Stack::Stack(Ressource type, int size) : 
  _size(size), _type(type) 
{
  
}

/// \brief return quantity of ressources inside the stack
int Stack::size() const {
  return _size;
}
/// \brief try to remove 'qty' of ressource from the stack
/// \return quantity removed : min(size, qty)
int Stack::reduce(int qty) {
  qty = std::min(_size, qty);
  _size -= qty;
  return qty;
}
/// \brief empty the stack
void Stack::clear() {
  _size = 0;
  _type = Invalid;
}

/// \brief return stack type
Stack::Ressource Stack::type() const {
  return _type;
}

/// \brief return true if the stack is empty
bool Stack::empty() const {
  return _size <= 0;
}

bool StackTypeComp::operator() (const Stack & a, const Stack & b) const {
  return a.type() < b.type();
}

std::size_t StackTypeHash::operator() (const Stack & a) const {
  return a.type();
}

bool StackTypeEqual::operator() (const Stack & a, const Stack & b) const {
  return a.type() == b.type();
}