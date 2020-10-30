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
/// \file   IIventory.h
/// \author tomato
///
/// \date 29 oct. 2020 15:54:16
///
#ifndef SOURCES_BUILTIN_GAME_INVENTORY_INVENTORY_H_
#define SOURCES_BUILTIN_GAME_INVENTORY_INVENTORY_H_

#include <game/Decorator.h>
#include <observer/SuperObserver.h>
#include <items/Stack.h>
#include <vector>

namespace builtin {
namespace game {
namespace inventory {

namespace Events {

struct Modified {
};
struct Full {
};
struct Empty {
};

}  // namespace Events

/// \brief Interface decorator for things that store other things
class Inventory: public ::game::Decorator, public SuperObserver::Subject< // @suppress("Invalid template argument")
    Inventory, Events::Modified, Events::Full, Events::Empty> {
public:

  /// \brief Unified object to return inventory content
  /// \todo turn it to a polymorphic object with iterator
  using Content = std::vector<items::Stack>;
  template<typename E>
  using Subject = SuperObserver::Subject<Inventory, E>; // @suppress("Invalid template argument")

  Inventory(const Pointer &ptr) noexcept :
      ::game::Decorator(ptr) {
  }
  virtual ~Inventory() noexcept = default;

  /// \brief try to add given stack to the inventory
  /// \return garbage aka ressources that cannot be added
  items::Stack add(const items::Stack &stack) noexcept {
    items::Stack garbage(doAdd(stack));
    if (garbage.size() != stack.size()) {
      Subject<Events::Modified>::notify(); // @suppress("Function cannot be resolved")
      if (isFull()) {
        Subject<Events::Full>::notify(); // @suppress("Function cannot be resolved")
      }
    }
    return garbage;
  }

  /// \brief try to remove given qty of given type from the inventory
  /// \return quantity successfully removed, can be empty if stack contains
  ///   no such ressources
  items::Stack reduce(items::Ressource type, int qty) noexcept {
    items::Stack result(doReduce(type, qty));
    if (!result.empty()) {
      Subject<Events::Modified>::notify(); // @suppress("Function cannot be resolved")
      if (isEmpty()) {
        Subject<Events::Empty>::notify(); // @suppress("Function cannot be resolved")
      }
    }
    return result;
  }

  /// \brief Must return quantity of given ressource that can be stored
  virtual int storableQtyOf(items::Ressource type) const noexcept = 0;
  /// \brief Must return true if inventory is empty
  virtual bool isEmpty() const noexcept = 0;
  /// \brief Must return true if inventory is full
  virtual bool isFull() const noexcept = 0;

  /// \brief Must return inventory content
  virtual Content content() const noexcept = 0;

  static const Kind TypeID() noexcept {
    static const Kind _id(Decorator::Hierarchy().newKind());
    return _id;
  }

protected:

  /// \brief Must Add given stack to the inventory
  /// \return garbage if full stack cannot be added
  virtual items::Stack doAdd(const items::Stack &stack) noexcept = 0;
  /// \brief Must try to get given stack from the inventory
  /// \brief type : Ressource type to take
  /// \brief qty  : Quantity to get, 0 for the maximum available
  /// \return a smaller one if request is bigger than inventory content
  virtual items::Stack doReduce(items::Ressource type, int qty) noexcept = 0;
};

}  // namespace inventory
}  // namespace game
}  // namespace builtin

#endif /* SOURCES_BUILTIN_GAME_INVENTORY_INVENTORY_H_ */
