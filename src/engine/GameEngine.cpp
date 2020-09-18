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
/// \file   GameEngine.cpp
/// \author Alexis CORREIA HENRIQUES <alex2ikangame@gmail.com>
///
/// \date 11 septembre 2020, 16:32
/// \brief Handler of in-game mechanics
///

#include <cassert>

#include "GameEngine.h"
#include "utils/hex/HexConsts.h"

/// \brief Contructor
GameEngine::GameEngine(WorldInterface & w) : 
  _peons(),
  _world(w)
{
  
}

/// \brief Add a peon in the game
void GameEngine::addPeon(Peon *p) {
  assert(_peons.insert(p).second);
  _world.addObject(p);
}

/// \brief Called on each Main-loop iteration
void GameEngine::update() {
  for (auto peon : _peons) {
    peonTick(peon);
  }
}


/// \brief Compute one tick of peon's behaviour
void GameEngine::peonTick(Peon *peon) {
  // Pass if nothing to do
  if (!peon->hasPath()) return;
  // Let's get it started
  const FlatHexPosition oldpos(peon->pos());
  // If target is reached we're done
  if (FlatHexPosition::distance(oldpos, peon->target()) < 0.02) {
    peon->endstep();
    if (!peon->hasPath()) 
       return;
    peon->beginStep();
  } 
  // Else compute one step
  else {
    // Compute default new position
    peon->pos(oldpos + peon->direction() * 0.01);
    // Check validity
    WorldObject *obstacle(nullptr);
    bool validMove(tryPosition(peon, &obstacle));
    // Try to find alternative path
    if (!validMove) {
      // World limit
      if (!obstacle) {
        LOG_TODO("Escape World Borders\n");
      } 
      // Round obstacle
      else {
        FlatHexPosition collide(obstacle->pos(), peon->pos());
        FlatHexPosition esc1(collide * hex::RMatrix_C60A);
        FlatHexPosition esc2(collide * hex::RMatrix_CC60A);
        FlatHexPosition & esc = esc1;
        if (
            FlatHexPosition::distance(oldpos + esc2 * 0.01, peon->target()) 
          < FlatHexPosition::distance(oldpos + esc1 * 0.01, peon->target())) 
        {
          esc = esc2;
        }
        peon->pos(oldpos + collide * 0.01);
        peon->addStep(oldpos + esc * obstacle->radius() * 2);
        peon->beginStep();
        validMove = true;
      }
    }
    if (validMove) {
      // If tile has changed move peon
      /// \bug Sometimes, tile is changed without passing this condition ...
      ///  if (oldpos.tile() != peon->pos().tile()) {
      ///  ...
      /// }
        FlatHexPosition tmp(peon->pos());
        peon->pos(oldpos);
        _world.removeObject(peon);
        peon->pos(tmp);
        _world.addObject(peon);
      // }
    } else {
      /// \todo Add notification if impossible path
      peon->pos(oldpos);
      peon->clearPath();
    }
  } /* else compute one step */
}

/// \brief Return true if given position is valid
///   if position is invalid, return false and return pointer to the obstacle
///   in 'obstacle' if relevants
bool GameEngine::tryPosition(Peon *peon, WorldObject **obstacle) const {
  // Check validity
  if (!_world.isOnMap(peon->pos())) {
    return false;
  }
  // Check collisions
  bool valid(true);
  peon->pos().mapNeightbours(
    [&]
    (const FlatHexPosition & pos) -> bool {
      auto content = _world.getContentAt(pos);
      if (content != nullptr){
        for (auto obj : *content){
          if (obj == peon) 
            continue;
          if (obj->collide(peon)) {
            *obstacle = obj;
            valid = false;
            return true;
          }
        }
      }
      return false;
    });
  return valid;
}
