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
/// \file   AbstractEntityBehaviour.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 06:14
///

#ifndef ABSTRACTENTITYBEHAVIOUR_H
#define ABSTRACTENTITYBEHAVIOUR_H

#include "engine/core/EngineInterface.h"
#include "engine/core/entity/EntityBehaviour.h"
#include "world/core/MapInterface.h"

class AbstractEntityBeh : public EntityBeh {
protected:
  GameEngineInterface&  _engine;
  MapInterface&         _map;
  
  AbstractEntityBeh(GameEngineInterface& engine, MapInterface& map) noexcept :
    _engine(engine), _map(map)
  {
  }
};

#endif /* ABSTRACTENTITYBEHAVIOUR_H */

