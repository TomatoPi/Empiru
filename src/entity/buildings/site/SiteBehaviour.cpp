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
/// \file   SiteBehaviour.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 6 octobre 2020, 14:38
///

#include "SiteBehaviour.h"
#include "ConstructSite.h"
#include "engine/GameEngine.h"

void SiteBehaviour::tick(WorldObject & obj, WorldPtr& ptr, WorldInterface & world) {
  ConstructionSite& site(static_cast<ConstructionSite&>(obj));
  if (!site.isFilled()) {
    return;
  }
  if (site.isFinished()) {
    GameEngine& engine(GameEngine::Get());
    WorldPtr building(engine.createObject(typeid(House), 
        [&] (WorldPtr& ptr) -> void {
          ptr->pos(obj.pos());
        }));
    float theta(0);
    for (WorldPtr worker : site.workers()) {
      float ro(building->radius() + worker->radius() + 0.1);
      worker->pos(building->pos() + WorldObject::Position::polar(ro, theta));
      world.addObject(worker);
      theta += 0.6;
    }
    engine.removeObject(ptr);
  }
  for (auto& worker : site.workers()) {
    (void)worker;
    site.progressTick(1);
  }
}