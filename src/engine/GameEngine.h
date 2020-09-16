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

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "world/World.h"
#include "entity/Peon.h"
#include <unordered_set>

class GameEngine {
private:

  typedef std::unordered_set<Peon*> PeonList;
  PeonList _peons;
  
  World *_world;
  
public:
  
  GameEngine(World *w);
  
  void addPeon(Peon *p);
  
  void update();
  
private:
  
  void peonTick(Peon *peon);

};

#endif /* GAMEENGINE_H */
