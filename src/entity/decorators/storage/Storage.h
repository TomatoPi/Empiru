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
#include "ressources/core/Stack.h"

class StorageDecorator : public Decorator {
private:
  
  /// \brief Table of Stack hashed by type
  typedef std::unordered_set<Stack, StackTypeHash, StackTypeEqual> StackList;
  StackList _storage; ///< Current storage
  
public:

  StorageDecorator() noexcept = default;
  virtual ~StorageDecorator() noexcept = default;
  
  /// \brief add given stack to the storage and return garbage
  Stack addToStorage(const Stack & stack) noexcept;
  
  const StackList & stock() const noexcept {
    return _storage;
  }
  
  bool canStore(Stack::Ressource type) const noexcept {
    return type != Stack::Ressource::Invalid
        && type != Stack::Ressource::Count;
  }
  
  virtual void setActive(bool status) noexcept override {/*nth*/}
  virtual bool isActive() const noexcept override {return true;}
  
public:
  
  class Builder : public Decorator::Builder {
  public :
    
    explicit Builder(const EntityPtr& entity) noexcept;
    
    virtual void operator() (DecoratorPtr& ptr) const noexcept override;
  };
};

#endif /* STORAGE_H */
