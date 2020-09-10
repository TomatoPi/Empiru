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
/// \file   HexMap.cpp
/// \author PORTEFAIX Maxime <portefaix.maxime@gmail.com>
///
/// \date 10 septembre 2020, 10:38
///

#include "HexMap.h"
#include <cassert>

/// \brief Constructor
HexMap::HexMap(
    int worldWidth, int worldHeight) :
  _worldWidth(worldWidth),
  _worldHeight(worldHeight)
    
{
  // assert(0 < worldWidth);
  // assert(0 < worldHeight);
}




HexMap * HexMap::generateFlatMap(int worldWidth, int worldHeight) {
    return new HexMap(worldWidth, worldHeight);
}
