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

#include <unordered_set>
#include "engine/core/decorator/Decorator.h"
#include "entity/decorators/inventory/Inventory.h"
#include "ressources/core/Stack.h"

namespace deco {
  class Storage : public Inventory {
  private:

    /// \brief Table of Stack hashed by type
    typedef std::array<Stack, Stack::RessourceCount> StackList;
    StackList _storage; ///< Current storage

  public:

    Storage() noexcept = default;
    virtual ~Storage() noexcept = default;
    
    virtual Stack add(const Stack& stack) noexcept override;
    virtual Stack reduce(Stack::Ressource type, int qty) noexcept override;
    virtual void clear() noexcept override;
    
    virtual bool canStore(Stack::Ressource type) const noexcept override;
    virtual bool isEmpty() const noexcept override;
    
    virtual Content content() const noexcept override;

  public:

    class Builder : public Inventory::Builder {
    private:
      
      StackList _maximums;
      
    public :

      explicit Builder(
        const EntityPtr& entity, 
        const std::initializer_list<Stack>& maximums) noexcept;

      virtual void operator() (DecoratorPtr& ptr) const noexcept override;
    };
  };
}
#endif /* STORAGE_H */
