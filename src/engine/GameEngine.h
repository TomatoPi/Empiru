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
/// \file   GameEngine.h
/// \author Alexis CORREIA HENRIQUES <alex2ikangame@gmail.com>
///
/// \date 11 septembre 2020, 16:32
/// \brief Handler of in-game mechanics
///

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "world/World.h"
#include "entity/peon/Peon.h"
#include <unordered_set>

/// \brief Core object for in-game mechanics
class GameEngine {
private:

  /// \brief Array used to store peons
  typedef std::unordered_set<Peon*> PeonList;
  
  PeonList         _peons; ///< List of living peons, peonhouettes and peonpeons
  WorldInterface & _world; ///< THA WO... oh wait ... joke already used
  
public:
  
  /// \brief Contructor
  GameEngine(WorldInterface & w);
  
  /// \brief Add a peon in the game
  void addPeon(Peon *p);
  
  /// \brief Called on each Main-loop iteration
  void update();
  
private:
  
  /// \brief Compute one tick of peon's behaviour
  void peonTick(Peon *peon);
  /// \brief Return true if given position is valid
  ///   if position is invalid, return false and return pointer to the obstacle
  ///   in 'obstacle' if relevant
  bool tryPosition(Peon *peon, WorldObject **obstacle) const;
};

#endif /* GAMEENGINE_H */
