/*
 * Copyright (C) 2020 PORTEFAIX Maxime <portefaix.maxime@gmail.com>
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
/// \file   HexMap.h
/// \author PORTEFAIX Maxime <portefaix.maxime@gmail.com>
///
/// \date 10 septembre 2020, 10:38
///

#ifndef HEXMAP_H
#define HEXMAP_H

#include "world/utils/WorldObject.h"
#include "gui/utils/Window.h"
#include <unordered_set>

class HexMap {
private:
  int _worldWidth;  ///< World's width in tile count
  int _worldHeight; ///< World height in tile count

  typedef std::unordered_set<Tile, WOTileHasher, WOTileEquals> WorldObjectSet;

  WorldObjectSet _map;
  
public:
  
    /// \brief Generate a flat map
   static HexMap * generateFlatMap(int worldWidth, int worldHeight);
 
private:
   /// \brief Constructor
   /// \param worldWidth : World's width in tile count
   /// \param worldHeight: World height in tile count
   HexMap(
          int worldWidth, int worldHeight);
};

#endif /* HEXMAP_H */
