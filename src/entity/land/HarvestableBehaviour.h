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
/// \file   HarvestableBehaviour.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 29 septembre 2020, 16:20
///

#ifndef HARVESTABLEBEHAVIOUR_H
#define HARVESTABLEBEHAVIOUR_H

#include "utils/world/WorldObject.h"
#include "utils/world/WorldInterface.h"
#include "utils/engine/Behaviourer.h"
#include "utils/world/Harvestable.h"
#include "engine/GameEngine.h"
#include "events/GameEvents.h"

class HarvestableBehaviour : public Behaviourer {
public:
  
  /// \brief Must compute one behaviour tick of obj
  virtual void tick(WorldObject& obj, WorldPtr& ptr, WorldInterface & world) {
    Harvestable & harvest(dynamic_cast<Harvestable &>(obj));
    if (harvest.empty()) {
      GameEngine::Get().removeObject(ptr);
    }
  }
};

#endif /* HARVESTABLEBEHAVIOUR_H */

