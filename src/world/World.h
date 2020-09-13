/*
 * Copyright (C) 2020 CHARAMOND Lucien <lucien.charamond@outlook.fr>
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
/// \file   World.h
/// \author CHARAMOND Lucien <lucien.charamond@outlook.fr>
///
/// \date 10 septembre 2020, 14:35
///

#ifndef  WORLD_H
#define WORLD_H

#include <unordered_map>

#include "Tile.h"
#include "utils/log.h"

/// \brief Object that handle Map and Objects
class World {
private :
  int _mapWidth;
  int _mapHeight;
  int* _map; /* Use for path finding and printing */
  typedef std::unordered_map<FlatHexPosition,Tile,HCHasher,HCEquals> ObjList;
  ObjList _objects; /*  */
 
public :
  ///\brief Constructor
  ///\param mapHeight : Height of the map (number of hexs)
  ///\param mapWidth : Width of the map (number of hexs)
  World(int mapWidth, int mapHeight);
  
  ///\brief Add an object to the world set
  ///\param obj :  object to add
  void addObject(Peon* pitou);

  /// \brief Get list of Peons at given pos
  /// \return nullptr if none
  const std::vector<Peon*> * getVectorFromPos(FlatHexPosition pos);
  
  ///\brief toString
  std::string toString() const;
  
  int width() const;  ///< World's width
  int height() const; ///< World's height
  ObjList objects() const; ///< List objects
};

#endif /* WORLD_H*/

