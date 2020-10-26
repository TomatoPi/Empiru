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
#include "objects/decorator/Builder.h"

#include <array>

namespace decorators {
  class Storage : public Inventory {
  private:

    /// \brief Table of Stack hashed by type
    typedef std::array<Stack, Stack::RessourceCount> StackList;
    StackList _storage; ///< Current storage

  public:

    Storage() noexcept = default;
    virtual ~Storage() noexcept = default;
    
    int storableQtyOf(Stack::Ressource type) const noexcept override;
    bool isEmpty() const noexcept override;
    bool isFull() const noexcept override;
    
    Content content() const noexcept override;
    
  protected:
    
    Stack doAdd(const Stack& stack) noexcept override;
    Stack doReduce(Stack::Ressource type, int qty) noexcept override;

  public:

    class Builder : public Decorator::Builder {
    private:
      
      StackList _maximums;
      
    public :

      explicit Builder(
        const core::Pointer& entity, 
        const std::initializer_list<Stack>& maximums) 
      noexcept;
      
      void operator() (core::Pointer& ptr) noexcept override;
    };
  };
}
#endif /* STORAGE_H */
