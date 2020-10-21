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
/// \file   AbstractEntityController.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 06:09
///

#ifndef ABSTRACTENTITYCONTROLLER_H
#define ABSTRACTENTITYCONTROLLER_H

#include "EntityControllerInterface.h"

class AbstractEntityController {
protected:
  
  IWorldMap&            _world;     ///< THA WORLDOOOOO
  IGameAllocator&     _engine;    ///< The Core of the GAMEUUH
  GameControllerInterface& _controller;
  
  AbstractEntityController(
    IWorldMap&            world,
    IGameAllocator&     engine,
    GameControllerInterface& controller)
  noexcept :
    _world(world), _engine(engine), _controller(controller)
  {
  }
};

#endif /* ABSTRACTENTITYCONTROLLER_H */

