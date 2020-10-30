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
/// \file   Deposit.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 19:02
///
#ifndef DEPOSIT_H
#define DEPOSIT_H

#include "../Inventory.h"
#include <cassert>

namespace builtin {
namespace game {
namespace inventory {

class Deposit: public Inventory {
private:

  items::Stack _stack;
  int _difficulty;

public:

  Deposit(const Pointer &ptr) noexcept :
      Inventory(ptr), _stack(), _difficulty(0) {
  }
  virtual ~Deposit() noexcept = default;

  int difficulty() const noexcept {
    return _difficulty;
  }

  /// \brief Must return true if given type can be added to the inventory
  int storableQtyOf(items::Ressource) const noexcept override {
    return 0;
  }
  /// \brief Must return true if inventory is empty
  bool isEmpty() const noexcept override {
    return _stack.empty();
  }
  bool isFull() const noexcept override {
    return _stack.full();
  }

  /// \brief Must return inventory content
  Content content() const noexcept override {
    return Content { _stack };
  }

  static const Kind TypeID() noexcept {
    static const Kind _id(Decorator::Hierarchy().newKind(Inventory::TypeID()));
    return _id;
  }

protected:

  /// \brief Must Add given stack to the inventory
  /// \return garbage if full stack cannot be added
  items::Stack doAdd(const items::Stack &stack) noexcept override {
    assert(0 && "invalid operation");
    return items::Stack();
  }
  /// \brief Must try to get given stack from the inventory
  /// \brief type : Ressource type to take
  /// \brief qty  : Quantity to get, 0 for the maximum available
  /// \return a smaller one if request is bigger than inventory content
  items::Stack doReduce(items::Ressource type, int qty) noexcept override {
    assert(type == _stack.type());
    return _stack.reduce(qty);
  }

public:

  struct Builder: public Decorator::Builder {

    int difficulty;
    int size;
    items::Ressource type;

    virtual ~Builder() noexcept = default;
    void operator()(Pointer &ptr) noexcept override {
      this->Decorator::Builder::operator ()(ptr);
      Deposit &deposit(ptr->as<Deposit>());
      deposit._difficulty = difficulty;
      deposit._stack = items::Stack(type, size);
    }
  };
};

}  // namespace inventory
}  // namespace game
}  // namespace builtin

#endif /* DEPOSIT_H */
