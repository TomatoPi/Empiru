/*
 * Copyright (C) 2020 Alexis
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
/// \author Alexis CORREIA HENRIQUES <alex2ikangame@gmail.com>
///
/// \date 11 septembre 2020, 16:32
/// \brief Handler of in-game mechanics
///

#include <cassert>

#include "GameEngine.h"

GameEngine::GameEngine(World *w) : 
  _peons(),
  _world(w)
{
  
}

void GameEngine::addPeon(Peon *p) {
  assert(_peons.insert(p).second);
  _world->addObject(p);
}

void GameEngine::update() {
  for (auto peon : _peons) {
    peonTick(peon);
  }
}

void GameEngine::peonTick(Peon *peon) {
  FlatHexPosition pos(peon->pos());
  if (FlatHexPosition::distance(pos, peon->targetPos()) < 0.02) {
    peon->pos(peon->targetPos());
  } else {
    peon->pos(pos + peon->direction() * 0.01);
    if (pos.tile() != peon->pos().tile()) {
      _world->removeObject(pos, peon);
      _world->addObject(peon);
    }
  }
}