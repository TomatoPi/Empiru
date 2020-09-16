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
/// \file   World.cpp
/// \author CHARAMOND Lucien <lucien.charamond@outlook.fr>
///
/// \date 10 septembre 2020, 14:34
///

#include <cassert>

#include "world/World.h"


World::World(int mapWidth, int mapHeight) :
  _mapWidth(mapWidth),
  _mapHeight(mapHeight),
  _map()
{
  assert(0 < mapWidth);
  assert(0 < mapHeight);
}


void World::addObject(WorldObject * obj){
  const FlatHexPosition & pos(obj->pos());
  auto itr(_map.find(pos));
  if (itr == _map.end()) {
    itr = _map.emplace(pos,Tile()).first;
  }
  itr->second.insert(obj);
}
void World::removeObject(const FlatHexPosition & pos, WorldObject * obj) {
  auto itr(_map.find(pos));
  assert(itr != _map.end());
  itr->second.erase(obj);
  if (itr->second.isEmpty()) {
    _map.erase(itr);
  }
}

const Tile::Content * World::getContentAt(const FlatHexPosition & pos) const {
  auto itr(_map.find(pos));
  if (itr != _map.end()){
    return &itr->second.getContent();
  }
  return nullptr;
}

bool World::isOnMap(const FlatHexPosition & pos) const {
  FlatHexPosition off(pos.tile().convert(FlatHexPosition::OddQOffset));
  return 0 <= off._x && 0 <= off._y 
      && off._x < _mapWidth
      && off._y < _mapHeight;
}