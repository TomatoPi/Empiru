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

#ifndef WORKER_H
#define WORKER_H

#include "engine/core/decorator/Decorator.h"
#include "engine/core/decorator/DecoratorPtr.h"
#include "ressources/core/Stack.h"

namespace decorator {
  
  class Worker : public Decorator {
  public:

    enum class Status {
      Idle,
      TooFar,
      Working,
      WorkDone,
      CannotWork
    };

  protected:

    DecoratorPtr  _worksite;
    Status        _status;

  public:

    Worker() noexcept = default;
    virtual ~Worker() noexcept = default;

    /// \brief Change the collect site of this collector
    void setWorkSite(const DecoratorPtr& ptr) noexcept;
    DecoratorPtr worksite() const noexcept;
    
    /// \brief Return the collector's status
    Status status() const noexcept;
    /// \brief Update collector's status
    Status updateStatus() noexcept;
    
    /// \brief Compute one collect tick
    void work() noexcept;
    
  protected:
    
    virtual void workChanged() noexcept = 0;
    virtual void doWork() noexcept = 0;
    virtual bool isWorkDone() const noexcept = 0;

  public:

    class Builder : public Decorator::Builder {
    public :

      explicit Builder(const EntityPtr& entity) noexcept :
        Decorator::Builder(entity) {}

      virtual void operator() (DecoratorPtr& ptr) const noexcept override {
        this->Decorator::Builder::operator() (ptr);
        this->addMarkers(ptr, typeid(Worker));
      }
    };
  };
}
#endif /* WORKER_H */
