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

#include "utils/World.h"
#include "engine/controller.h"

World::World(int mapWidth, int mapHeight) : 
    _objects(),
    _mapWidth(mapWidth),
    _mapHeight(mapHeight){
  assert(0 < mapWidth);
  assert(0 < mapHeight);
  _map = new int[mapWidth*mapHeight];
  for (int i; i<mapWidth*mapHeight;i++){
    _map[i] = 0;
  }
}

void World::addObject(Peon pitou){
  FlatHexPosition pitou_pos = pitou.pos();
  if (_objects.find(pitou_pos) != _objects.end()){
    _objects.find(pitou_pos).insert();
  }else{
    _objects.insert(std::make_pair(pitou_pos,pitou));
    _objects.find(pitou_pos).insert(std::make_pair(pitou_pos,pitou));
  }
}

std::string World::toString() const{
  std::string ts = "[Map Height : ";
  ts.append(std::to_string(_mapHeight))
    .append(", Map Width : ")
    .append(std::to_string(_mapWidth))
    .append("]\n");
  for(int i = 0; i <_mapHeight*_mapWidth;i++){
    if (i%_mapWidth == 0){
      ts = ts.append("\n");
    }
    ts.append(std::to_string(_map[i]))
      .append(" ");
  }
  ts.append("\n");
  /*for(Tile wo : _objects){
    ts.append(wo.toString()).append("\n");
  }*/
  return ts.append("\n");
}