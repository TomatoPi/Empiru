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
/// \file   Collector.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 22:18
///

#ifndef COLLECTOR_H
#define COLLECTOR_H

#include "engine/core/decorator/Decorator.h"
#include "ressources/core/Stack.h"

class CollectorDecorator : public Decorator {
private:
  
  Stack _inventory;
  
  
public:

  CollectorDecorator() noexcept : _inventory() {}
  virtual ~CollectorDecorator() noexcept = default;
  
  virtual void setActive(bool status) noexcept override {/*nth*/}
  virtual bool isActive() const noexcept override {return true;}
  
public:
  
  class Builder : public Decorator::Builder {
  private:
    
    int              _size;
    Stack::Ressource _type;
    
  public :
    
    explicit Builder(const EntityPtr& entity) noexcept;
    
    virtual void operator() (DecoratorPtr& ptr) const noexcept override;
  };
};

#endif /* COLLECTOR_H */
