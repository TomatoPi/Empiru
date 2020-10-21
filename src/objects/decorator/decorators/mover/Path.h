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
/// \file   Mover.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 08:27
///

#ifndef DECORATOR_PATH_H
#define DECORATOR_PATH_H

#include <vector>
#include "engine/core/decorator/Decorator.h"
#include "world/core/WorldObject.h"
#include "world/core/MapInterface.h"
#include "utils/hex/Axial.h"

namespace decorator {
  class Path : public Decorator {
  public:

    enum class Event {
      TargetChanged,
      TargetReached,
      PathObstructed,
    };
    
    class Observer {
    public:
      virtual void onNotify(const DecoratorPtr&, Event) noexcept = 0;
    };

  private:

    std::vector<WorldObject::Position> _target;
    hex::Axial                         _dir;
    float                              _tolerance;
    float                              _speed;
    Status                             _status;

  public:

    Path() noexcept = default;
    virtual ~Path() noexcept = default;
    void setTarget(const WorldObject::Position& target, float tolerance) noexcept;

  private:

    void clearPath() noexcept;
    void stackTarget(const WorldObject::Position& target) noexcept;
    void unstackTarget() noexcept;

  public:

    class Builder : public Decorator::Builder {
    private:

      float _speed;

    public :

      explicit Builder(const EntityPtr& entity, float speed=0.01) noexcept;

      virtual void operator() (DecoratorPtr& ptr) const noexcept override;
    };
  };
}

#endif /* DECORATOR_PATH_H */

