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

#include "world/core/MapInterface.h"
#include "world/core/Tile.h"
#include "utils/log.h"

/// \brief Object that handle Map and Objects
class WorldMap : public MapInterface {
private :
  
  /// \brief Hollow Matrix
  typedef std::unordered_map<
      WorldObject::Position,
      Tile,
      hex::Axial::TileHasher,
      hex::Axial::TileEquals> 
    ObjList;
  
  int _mapWidth;  ///< Horizontal tile count
  int _mapHeight; ///< Verical tile count
  ObjList _map;   ///< Hollow matrix of world content
 
public :
  
  /// \brief Constructor
  /// \param mapHeight : Height of the map (number of hexs)
  /// \param mapWidth : Width of the map (number of hexs)
  WorldMap(int mapWidth, int mapHeight);
  
  /// \brief Must add given object to the world
  virtual void addObject(const EntityPtr& ptr) override;
  /// \brief Must remove given object fro the world
  virtual void removeObject(const EntityPtr& ptr) override;
  
  /// \brief Must return tile content at given pos, or null if empty
  virtual const Tile::Content * getContentAt(const WorldObject::Position & pos) const override;
  
  /// \brief Must return true if given pos is on the map
  virtual bool isOnMap(const WorldObject::Position & pos) const override;
  
  /// \brief Return true if given position is valid
  ///   if position is invalid, return false and return pointer to the obstacle
  ///   in 'obstacle' if relevant
  virtual bool tryPosition(
    const WorldObject& obj, 
    const EntityPtr& entity, 
    EntityPtr* obstacle) const noexcept override;
};

#endif /* WORLD_H*/
