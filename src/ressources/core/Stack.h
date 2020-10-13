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
#include <limits>
#include <cassert>

/// \brief Represents a ressource stack
class Stack {
public:
  
  /// \brief Enum of all ressources kind
  enum class Ressource {
    Invalid,
    Wood,
    Rock,
    Count
  };
  
  static constexpr std::size_t RessourceCount = static_cast<std::size_t>(Ressource::Count);
  static constexpr std::size_t RessourceBegin = static_cast<std::size_t>(Ressource::Wood);
  static constexpr std::size_t RessourceEnd   = static_cast<std::size_t>(Ressource::Rock);
  
private:
  
  int       _size;
  int       _max;
  Ressource _type;
  
public:
  
  /// \brief Default Constructor, build invalid ressource
  Stack() noexcept :
    Stack(Ressource::Invalid, 0, 0)
  {    
  }
  /// \brief Create a ressource of given type and size
  Stack(Ressource type, int size, int max=std::numeric_limits<int>::max()) noexcept :
    _size(size), 
    _max(type == Ressource::Count ? 0 : type == Ressource::Invalid ? 0 : max),
    _type(type)
  {
  }
  
  /// \brief Default members
  Stack(const Stack &) noexcept = default;
  Stack & operator= (const Stack &) noexcept = default;
  ~Stack() noexcept = default;
  
  /// \brief return quantity of ressources inside the stack
  int size() const noexcept {
    return _size;
  }
  int max() const noexcept {
    return _max;
  }
  /// \brief return stack type
  Ressource type() const noexcept {
    return _type;
  }
  
  Stack add(const Stack& stack) noexcept {
    assert(_type != Ressource::Invalid);
    assert(_type != Ressource::Count);
    assert(stack._type == _type);
    int qty(std::min(_max - _size, stack._size));
    _size += qty;
    return Stack(_type, stack._size - qty);
  }
  Stack reduce(int qty) noexcept {
    assert(_type != Ressource::Invalid);
    assert(_type != Ressource::Count);
    qty = std::min(_size, qty);
    _size -= qty;
    return Stack(_type, qty);
  }
  
  void clear() noexcept {
    _size = 0;
  }
  
  /// \brief return true if the stack is empty
  bool empty() const noexcept {
    return _size <= 0 
        || _type == Ressource::Invalid
        || _type == Ressource::Count;
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
    return static_cast<std::size_t>(a.type());
  }
};

class StackTypeEqual {
public:
  bool operator() (const Stack & a, const Stack & b) const noexcept {
    return a.type() == b.type();
  }
};

#endif /* RESSOURCE_H */
