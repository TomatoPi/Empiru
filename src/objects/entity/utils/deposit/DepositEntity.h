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
/// \file   DepositEntity.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 20:02
///

#ifndef DEPOSITENTITY_H
#define DEPOSITENTITY_H

#include "core/IAllocator.h"
#include "objects/entity/core/Entity.h"
#include "objects/entity/core/Builder.h"
#include "objects/decorator/decorators/inventory/deposit/Deposit.h"
#include "objects/decorator/decorators/worldobj/Builder.h"

/// \brief The ultimate worker, useful to make anything you can think of
/// \todo revise the path system
class DepositEntity : public Entity::Base {
private:
  core::Pointer _deposit;
public:
    
    core::Pointer 
    doFindDecorator(const std::type_info& type) noexcept override;
    const core::Pointer 
    doFindDecorator(const std::type_info& type) const noexcept override;

    /// \brief Useful to get and cast a decorator to a subtype
    template <class T>
    T& get() noexcept {
      return Entity::Base::get<T>();
    }
    /// \brief Useful to get and cast a decorator to a subtype
    template <class T>
    const T& get() const {
      return Entity::Base::get<T>();
    }
  
  class Builder : public Entity::Builder {
  private:
    
    Stack::Ressource     _type;
    int                  _qty;
    
  public:
    
    Builder(
      const world::Position& pos,
      Stack::Ressource type, int qty) 
    noexcept;
    
    void operator() (core::Pointer& ptr) noexcept override;
  };
};

template <>
decorators::Deposit& DepositEntity::get() noexcept {
  return static_cast<decorators::Deposit&>(*_deposit);
}

template <>
const decorators::Deposit& DepositEntity::get() noexcept {
  return static_cast<const decorators::Deposit&>(*_deposit);
}

template <>
decorators::Inventory& DepositEntity::get() noexcept {
  return static_cast<decorators::Inventory&>(*_deposit);
}

template <>
const decorators::Inventory& DepositEntity::get() noexcept {
  return static_cast<const decorators::Inventory&>(*_deposit);
}

#endif /* DEPOSITENTITY_H */

