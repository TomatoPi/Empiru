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

#include "utils/world/WorldInterface.h"
#include "utils/world/Tile.h"
#include "utils/log.h"

/// \todo Découpler l'implementation de la map de son utilisation 
///   via une interface
/// \todo Ajouter le retrait d'objets
/// \brief Object that handle Map and Objects
class World : public WorldInterface {
private :
  
  typedef std::unordered_map<FlatHexPosition,Tile,HCHasher,HCEquals> ObjList;
  
  int _mapWidth;
  int _mapHeight;
  ObjList _map;
 
public :
  /// \brief Constructor
  /// \param mapHeight : Height of the map (number of hexs)
  /// \param mapWidth : Width of the map (number of hexs)
  World(int mapWidth, int mapHeight);
  
  virtual void addObject(WorldObject * obj);
  virtual void removeObject(WorldObject * obj);
  
  virtual const Tile::Content * getContentAt(const FlatHexPosition & pos) const;
  
  virtual bool isOnMap(const FlatHexPosition & pos) const;
};

#endif /* WORLD_H*/

