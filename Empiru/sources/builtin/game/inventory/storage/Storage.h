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
/// \file   Storage.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 22:22
///
#ifndef STORAGE_H
#define STORAGE_H

#include "../Inventory.h"
#include <items/StackHelpers.h>
#include <map>

namespace builtin {
namespace game {
namespace inventory {

class Storage: public Inventory {
private:

  /// \brief Table of Stack hashed by type
  using StackList = std::map<items::Ressource, items::Stack>; // @suppress("Invalid template argument")
  StackList _storage; ///< Current storage

public:

  Storage(const Pointer &ptr) noexcept :
      Inventory(ptr) {
  }
  virtual ~Storage() noexcept = default;

  int storableQtyOf(items::Ressource type) const noexcept override;
  bool isEmpty() const noexcept override;
  bool isFull() const noexcept override;

  Content content() const noexcept override;

  static const Kind TypeID() noexcept {
    static const Kind _id(Decorator::Hierarchy().newKind(Inventory::TypeID()));
    return _id;
  }

protected:

  items::Stack doAdd(const items::Stack &stack) noexcept override;
  items::Stack doReduce(items::Ressource type, int qty) noexcept override;

public:

  struct Builder: public Decorator::Builder {
    std::initializer_list<std::pair<items::Ressource, int>> maxes;
    void operator()(Pointer &ptr) noexcept override;
  };
};

}  // namespace inventory
}  // namespace game
}  // namespace builtin

#endif /* STORAGE_H */
