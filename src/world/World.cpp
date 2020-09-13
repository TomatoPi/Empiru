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
  _map(nullptr),
  _objects()
{
  assert(0 < mapWidth);
  assert(0 < mapHeight);
  _map = new int[mapWidth*mapHeight];
  for (int i; i<mapWidth*mapHeight;i++){
    _map[i] = 0;
  }
}


void World::addObject(Peon *pitou){
  const FlatHexPosition & pitou_pos = pitou->pos();
  auto itr = _objects.find(pitou_pos);
  if (itr == _objects.end()) {
    itr = _objects.emplace(pitou_pos,Tile(pitou_pos, pitou)).first;
  }
  else {
    itr->second.insert(pitou);
  }
}

const std::vector<Peon*> * World::getVectorFromPos(FlatHexPosition pos){
  if (_objects.find(pos) != _objects.end()){
    return _objects.find(pos)->second.getVector();
  }
  return nullptr;
}

std::string World::toString() const{
  std::string ts = "[Map Height : ";
  ts.append(std::to_string(_mapHeight))
    .append(", Map Width : ")
    .append(std::to_string(_mapWidth))
    .append("]\n");
  
  for (auto & itr : _objects){
    ts.append(std::to_string(itr.second.pos()._x))
      .append("/")
      .append(std::to_string(itr.second.pos()._y))
      .append("/")
      .append(std::to_string(itr.second.pos()._y))
      .append("\n");
  }
  /*
  for(int i = 0; i <_mapHeight*_mapWidth;i++){
    if (i%_mapWidth == 0){
      ts = ts.append("\n");
    }
    ts.append(std::to_string(_map[i]))
      .append(" ");
  }
  */
  //ts.append("\n");
  /*for(Tile wo : _objects){
    ts.append(wo.toString()).append("\n");
  }*/
  return ts;//.append("\n");
}
int World::width() const {
  return _mapWidth;
}
int World::height() const {
  return _mapHeight;
}

World::ObjList World::objects() const {
  return _objects;
}