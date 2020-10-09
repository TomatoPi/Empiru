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
/// \file   ConstructSite.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 30 septembre 2020, 11:20
///

#ifndef CONSTRUCTSITE_H
#define CONSTRUCTSITE_H

#include <unordered_set>

#include "utils/world/core/WorldObject.h"
#include "utils/world/core/EntityPtr.h"
#include "utils/world/Recipe.h"
#include "utils/log.h"

#include "entity/buildings/warehouse/Warehouse.h"
#include "entity/buildings/house/House.h"
#include "ConstructionGhost.h"

class ConstructionSite : public WorldObject, public Recipe {
public:
  
  typedef std::unordered_set<WorldPtr,core::PtrHash,core::PtrEquals> WorkersList;
  
private:

  WorkersList _workers;
  const std::type_info* _type;
  
  int _progress;
  int _cptr;
  int _difficulty;
  
public:
  ConstructionSite();
  ConstructionSite(const ConstructionSite &) = default;
  ConstructionSite & operator= (const ConstructionSite &) = default;
  
  int progress() const noexcept;
  bool isFinished() const noexcept;
  void progressTick(int speed);
  
  void addWorker(const WorldPtr& ptr);
  void removeWorker(const WorldPtr& ptr);
  const WorkersList& workers() const noexcept;
  
  const std::type_info& type() const noexcept;
  
  struct Builder {
    const ConstructionGhost& _ghost;
    Builder(const ConstructionGhost& ghost) noexcept : _ghost(ghost) {}
    void operator() (WorldPtr& ptr) const noexcept {
      ConstructionSite& site = static_cast<ConstructionSite&>(*ptr);
      site.pos(_ghost.pos());
      site._progress = 0;
      site._type = &_ghost.type();
      if (typeid(House) == _ghost.type()) {
        //site.setRecipe({Stack(Stack::Wood, 50), Stack(Stack::Rock, 10)});
        site._difficulty = 1;
      }
      else if (typeid(Warehouse) == _ghost.type()) {
        site.setRecipe({Stack(Stack::Wood, 100), Stack(Stack::Rock, 10)});
        site._difficulty = 40;
      } 
      else {
        LOG_TODO("Build a %s\n", _ghost.type().name());
        assert(0);
      }
    }
  };
};

#endif /* CONSTRUCTSITE_H */
