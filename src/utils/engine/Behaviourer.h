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
/// \file   Behaviourer.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 18 septembre 2020, 17:06
/// \brief Interface for WorldObjects mechanics' handlers
///

#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include "utils/world/map/MapInterface.h"
#include "utils/world/core/WorldObject.h"
#include "utils/world/core/WorldPtr.h"

/// \brief Interface for WorldObjects mechanics' handlers
class Behaviourer {
public:
  
  /// \brief Must compute one behaviour tick of obj
  virtual void tick(WorldObject& obj, WorldPtr& ptr, MapInterface& world) = 0;
};

#endif /* BEHAVIOUR_H */

