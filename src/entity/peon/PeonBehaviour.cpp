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
/// \file   PeonBehaviour.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 18 septembre 2020, 19:18
///

#include <cassert>

#include "PeonBehaviour.h"

#include "utils/hex/HexConsts.h"
#include "utils/log.h"

/// \brief Must compute one behaviour tick of obj
void PeonBehaviour::tick(WorldObject & obj, WorldRef *ref, WorldInterface & world) {
  Peon & peon(static_cast<Peon &>(obj));
  // Pass if nothing to do
  if (!peon.hasPath()) return;
  // Let's get it started
  const FlatHexPosition oldpos(peon.pos());
  // If target is reached we're done
  if (FlatHexPosition::distance(oldpos, peon.target()) < 0.02) {
    world.removeObject(ref);
    peon.endstep();
    world.addObject(ref);
    if (!peon.hasPath()) 
       return;
    peon.beginStep();
  } 
  // Else compute one step
  else {
    // Compute default new position
    peon.pos(oldpos + peon.direction() * 0.01);
    // Check validity
    WorldObject *obstacle(nullptr);
    bool validMove(tryPosition(peon, ref, &obstacle, world));
    // Try to find alternative path
    if (!validMove) {
      // World limit
      if (!obstacle) {
        LOG_TODO("Escape World Borders\n");
      } 
      // Round obstacle
      else {
        FlatHexPosition collide(obstacle->pos(), peon.pos());
        FlatHexPosition esc1(collide * hex::RMatrix_C60A);
        FlatHexPosition esc2(collide * hex::RMatrix_CC60A);
        FlatHexPosition & esc = esc1;
        if (
            FlatHexPosition::distance(oldpos + esc2 * 0.01, peon.target()) 
          < FlatHexPosition::distance(oldpos + esc1 * 0.01, peon.target())) 
        {
          esc = esc2;
        }
        peon.pos(oldpos + collide * 0.01);
        peon.addStep(oldpos + esc * obstacle->radius() * 2);
        peon.beginStep();
        validMove = true;
      }
    }
    if (validMove) {
      // If tile has changed move peon
      if (oldpos.tile() != peon.pos().tile()) {
        FlatHexPosition tmp(peon.pos());
        peon.pos(oldpos);
        world.removeObject(ref);
        peon.pos(tmp);
        world.addObject(ref);
      }
    } else {
      /// \todo Add notification if impossible path
      peon.pos(oldpos);
      peon.clearPath();
    }
  } /* else compute one step */
}

/// \brief Return true if given position is valid
///   if position is invalid, return false and return pointer to the obstacle
///   in 'obstacle' if relevant
bool PeonBehaviour::tryPosition(
    Peon & peon, WorldRef *ref, WorldObject ** obstacle, WorldInterface & world)
const {
  // Check validity
  if (!world.isOnMap(peon.pos())) {
    return false;
  }
  // Check collisions
  bool valid(true);
  peon.pos().mapNeightbours(
    [&]
    (const FlatHexPosition & pos) -> bool {
      auto content = world.getContentAt(pos);
      if (content != nullptr){
        for (auto obj : *content){
          if (obj == ref) 
            continue;
          if ((**obj).collide(peon)) {
            *obstacle = &(**obj);
            valid = false;
            return true;
          }
        }
      }
      return false;
    });
  return valid;
}