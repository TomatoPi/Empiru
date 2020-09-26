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
/// \file   Ressource.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 21 septembre 2020, 19:30
///

#ifndef RESSOURCE_H
#define RESSOURCE_H

#include <cstddef>

/// \brief Represents a ressource stack
class Stack {
public:
  
  /// \brief Enum of all ressources kind
  enum Ressource {
    Invalid,
    Wood,
    Rock
  };
  
private:
  
  int       _size;
  Ressource _type;
  
public:
  
  /// \brief Default Constructor, build invalid ressource
  Stack() noexcept :
    Stack(Invalid, 0)
  {    
  }
  /// \brief Create a ressource of given type and size
  Stack(Ressource type, int size) noexcept :
    _size(size), _type(type)
  {
  }
  /// \brief Default members
  Stack(const Stack &) = default;
  Stack & operator= (const Stack &) = default;
  ~Stack() = default;
  
  /// \brief return quantity of ressources inside the stack
  int size() const noexcept {
    return _size;
  }
  /// \brief try to remove 'qty' of ressource from the stack
  /// \return quantity removed : min(size, qty)
  int reduce(int qty) noexcept {
    qty = std::min(_size, qty);
    _size -= qty;
    return qty;
  }
  /// \brief empty the stack
  void clear() noexcept {
    _size = 0;
    _type = Invalid;
  }
  
  /// \brief return stack type
  Ressource type() const noexcept {
    return _type;
  }
  
  /// \brief return true if the stack is empty
  bool empty() const noexcept {
    return _size <= 0;
  }
};

class StackTypeComp {
public:
  bool operator() (const Stack & a, const Stack & b) const noexcept {
    return a.type() < b.type();
  }
};

class StackTypeHash {
public:
  std::size_t operator() (const Stack & a) const noexcept {
    return a.type();
  }
};

class StackTypeEqual {
public:
  bool operator() (const Stack & a, const Stack & b) const noexcept {
    return a.type() == b.type();
  }
};

#endif /* RESSOURCE_H */
