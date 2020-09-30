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
/// \file   PeonBehaviour.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 18 septembre 2020, 19:18
///

#ifndef PEONBEHAVIOUR_H
#define PEONBEHAVIOUR_H

#include "entity/peon/Peon.h"
#include "utils/world/WorldObject.h"
#include "utils/world/WorldInterface.h"
#include "utils/engine/Behaviourer.h"

class PeonBehaviour : public Behaviourer {  
public:
  
  /// \brief Must compute one behaviour tick of obj
  virtual void tick(WorldObject& obj, WorldPtr& ptr, WorldInterface& world);
  
private:
  
  /// \brief compute harvest order
  void store(Peon& peon, WorldPtr& ptr, WorldInterface& world);
  
  /// \brief compute harvest order
  void harvest(Peon& peon, WorldPtr& ptr, WorldInterface& world);
  
  /// \brief compute path order for the peon
  void moveTo(Peon& peon, WorldPtr& ptr, WorldInterface& world);
  
  /// \brief Return true if given position is valid
  ///   if position is invalid, return false and return pointer to the obstacle
  ///   in 'obstacle' if relevant
  bool tryPosition(
        Peon& peon, 
        WorldPtr& ptr, 
        WorldObject** obstacle, 
        WorldInterface& world)  
    const;
};

#endif /* PEONBEHAVIOUR_H */
