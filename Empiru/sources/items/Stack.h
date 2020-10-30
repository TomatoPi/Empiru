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
/// \file   Stack.h
/// \author tomato
///
/// \date 29 oct. 2020 17:57:25
///
#ifndef SOURCES_ITEMS_STACK_H_
#define SOURCES_ITEMS_STACK_H_

#include "Ressource.h"

namespace items {

/// \brief Represents a ressource stack
class Stack {
private:

  Ressource _type;
  int _size;
  int _max;

public:
  /// \brief Create a ressource of given type and size
  Stack(Ressource type = Ressource::Invalid(), int size = 0, int max =
      std::numeric_limits<int>::max()) noexcept :
      _type(type), _size(type == Ressource::Invalid() ? 0 : size), _max(
          type == Ressource::Invalid() ? 0 : max) {
  }

  /// \brief Default members
  Stack(const Stack&) noexcept = default;
  Stack& operator=(const Stack&) noexcept = default;
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

  Stack add(const Stack &stack) noexcept {
    assert(_type != Ressource::Invalid());
    assert(stack._type == _type);
    int qty(std::min(_max - _size, stack._size));
    _size += qty;
    return Stack(_type, stack._size - qty);
  }
  Stack reduce(int qty) noexcept {
    assert(_type != Ressource::Invalid());
    qty = std::min(_size, qty);
    _size -= qty;
    return Stack(_type, qty);
  }

  void clear() noexcept {
    _size = 0;
  }

  /// \brief return true if the stack is empty
  bool empty() const noexcept {
    return _size <= 0 || _type == Ressource::Invalid();
  }
  /// \brief return true if the stack is empty
  bool full() const noexcept {
    return _max <= _size || _type == Ressource::Invalid();
  }
};

}  // namespace items

#endif /* SOURCES_ITEMS_STACK_H_ */
