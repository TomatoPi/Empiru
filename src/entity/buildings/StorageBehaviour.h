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
/// \file   StorageBehaviour.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 29 septembre 2020, 00:44
///

#ifndef STORAGEBEHAVIOUR_H
#define STORAGEBEHAVIOUR_H

#include "entity/functionals/TribeInfos.h"
#include "utils/world/core/WorldObject.h"
#include "utils/world/map/MapInterface.h"
#include "utils/engine/Behaviourer.h"
#include "utils/world/Storage.h"

class StorageBehaviour : public Behaviourer {
private:
  
  TribeInfos & _infos;
  
public:
  
  StorageBehaviour(TribeInfos & infos) : 
    _infos(infos)
  {      
  }
  
  /// \brief Must compute one behaviour tick of obj
  virtual void tick(WorldObject & obj, WorldPtr& ptr, MapInterface & world) {
    Storage & storage(dynamic_cast<Storage &>(obj));
    for (auto & stack : storage.stock()) {
      _infos.addStack(stack);
    }
  }
};

#endif /* STORAGEBEHAVIOUR_H */

