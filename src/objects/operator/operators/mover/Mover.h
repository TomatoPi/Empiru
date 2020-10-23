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
/// \date 22 octobre 2020, 21:01
///

#ifndef MOVER_H
#define MOVER_H

#include "objects/operator/core/Operator.h"
#include "world/core/IWorldMap.h"
#include "world/core/Types.h"

#include <vector>

class Mover : public Operator {
public:
  
  struct Event : public core::Object::Event {
    enum class Type {
      TargetReached,
      ObstructedPath,
    };
    Type type;
    explicit Event(Type t) noexcept : type(t) {}
  };
  
  class Builder : public Operator::Builder {
  private:

    IWorldMap*      _worldMap;
    core::Pointer   _object;
    float           _speed;

  public :

    Builder(
      IWorldMap* worldMap,
      const core::Pointer& object, 
      float speed) noexcept;

    virtual void operator() (core::Pointer& ptr) noexcept override;
  };
  
private:
  
  IWorldMap*                    _worldMap;
  core::Pointer                 _object;
  std::vector<world::Position>  _target;
  hex::Axial                    _dir;
  float                         _tolerance;
  float                         _speed;
  
public:
  
  Mover() noexcept = default;
  virtual ~Mover() noexcept = default;
  
  virtual bool operator() () noexcept override;
  
  void clear() noexcept;
  void setTarget(const world::Position& target, float tolerance) noexcept;
  
protected:

  /// \brief Must be called on events
  virtual void 
  doOnNotify(const core::Pointer& p, const core::Object::Event& e) 
  noexcept override;
  
private:
  
  void stackTarget(const world::Position& target) noexcept;
  void unstackTarget() noexcept;
};

#endif /* MOVER_H */
