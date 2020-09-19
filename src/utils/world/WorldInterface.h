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

/// \brief Interface that must be used to comunicate with the World
class WorldInterface {
public:
  
  /// \brief Must add given object to the world
  virtual void addObject(WorldRef * obj) = 0;
  /// \brief Must remove given object fro the world
  virtual void removeObject(WorldRef * obj) = 0;
  
  /// \brief Must return tile content at given pos, or null if empty
  virtual const Tile::Content * getContentAt(const FlatHexPosition & pos) const = 0;
  
  /// \brief Must return true if given pos is on the map
  virtual bool isOnMap(const FlatHexPosition & pos) const = 0;
};

#endif /* WORLDINTERFACE_H */

