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
/// \date 14 octobre 2020, 11:36
///

#ifndef COLLECTOR_H
#define COLLECTOR_H

#include "utils/misc/Counter.h"
#include "entity/decorators/worker/Worker.h"

namespace deco {
  
  class Collector : public Worker {
  private:
    
    enum class Action {
      Store,
      Collect
    };
    
    DecoratorPtr      _inventory;
    Counter           _cptr;
    Stack::Ressource  _target;
    Action            _action;
    
  public:
    
    Collector() noexcept = default;
    virtual ~Collector() noexcept = default;
    
    void collectAt(const DecoratorPtr& ptr, Stack::Ressource type) noexcept;
    void storeAt(const DecoratorPtr& ptr, Stack::Ressource type) noexcept;
    
  protected:
    
    virtual void workChanged() noexcept override;
    virtual void doWork() noexcept override;
    virtual bool isWorkDone() const noexcept override;
    
  public:
    
    class Builder : public Worker::Builder {
    public :

      explicit Builder(const EntityPtr& entity) noexcept;

      virtual void operator() (DecoratorPtr& ptr) const noexcept override;
    };
  };
}

#endif /* COLLECTOR_H */
