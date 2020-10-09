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

#include "engine/core/decorator/Decorator.h"
#include "ressources/core/Stack.h"

class DepositDecorator : public Decorator {
private:
  
  Stack _stack;
  
public:

  DepositDecorator() noexcept : _stack() {}
  virtual ~DepositDecorator() noexcept = default;
  
  int reduce(int qty) noexcept {return _stack.reduce(qty);}
  Stack::Ressource type() const noexcept {return _stack.type();}
  int size() const noexcept {return _stack.size();}
  bool empty() const noexcept {return _stack.empty();}
  
  virtual void setActive(bool status) noexcept override {/*nth*/}
  virtual bool isActive() const noexcept override {return !empty();}
  
public:
  
  class Builder : public Decorator::Builder {
  private:
    
    int              _size;
    Stack::Ressource _type;
    
  public :
    
    explicit Builder(const EntityPtr& entity, Stack::Ressource type, int size)
    noexcept;
    
    virtual void operator() (DecoratorPtr& ptr) const noexcept override;
  };
};

#endif /* DEPOSIT_H */
