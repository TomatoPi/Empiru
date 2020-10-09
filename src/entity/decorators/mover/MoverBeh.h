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
/// \file   MoverBeh.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 09:33
///

#ifndef MOVERBEH_H
#define MOVERBEH_H

#include "Mover.h"
#include "engine/core/decorator/DecoratorBehaviour.h"
#include "world/core/MapInterface.h"

class MoverDecoratorBeh : public DecoratorBeh {
private:
  
  MapInterface& _map;
  
public:
  
  MoverDecoratorBeh(MapInterface& m) noexcept : _map(m) {}
  
  virtual void 
  operator() (Decorator& decorator, DecoratorPtr) noexcept override {
    static_cast<MoverDecorator&>(decorator).walk(_map);
  }
};

#endif /* MOVERBEH_H */

