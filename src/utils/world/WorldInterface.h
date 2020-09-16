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
/// \file   WorldInterface.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 16 septembre 2020, 10:47
///

#ifndef WORLDINTERFACE_H
#define WORLDINTERFACE_H

#include "utils/world/Tile.h"

class WorldInterface {
public:
  
  virtual void addObject(WorldObject * obj) = 0;
  virtual void removeObject(const FlatHexPosition & pos, WorldObject * obj) = 0;
  
  virtual const Tile::Content * getContentAt(const FlatHexPosition & pos) const = 0;
  
  virtual bool isOnMap(const FlatHexPosition & pos) const = 0;
};

#endif /* WORLDINTERFACE_H */

