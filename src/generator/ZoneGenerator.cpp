/*
 * Copyright (C) 2020 Alexis
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

/* 
 * File:   ZoneGenerator.cpp
 * Author: Alexis
 * 
 * Created on 20 septembre 2020, 17:00
 */

#include "ZoneGenerator.h"
#include "world/World.h"
#include <random>
#include <algorithm>

ZoneGenerator::ZoneGenerator() : _vertexs(), _objects() {
  
}

void ZoneGenerator::createZone(int size) {
  for (int i = 0 ; i < size ; i++){
    hex::Axial position = hex::Axial((rand()%10),(rand()%10));
    _vertexs.push_back(position);
  }
  
  std::sort(_vertexs.begin(), _vertexs.end(), 
  [&]
  (const hex::Axial & a, const hex::Axial & b) -> bool {
    return a._x < b._x;
  });
  
}

void ZoneGenerator::addObject() {
  int nb_object = 10;
  float xRand,yRand;
  float y1,y2;
  
  std::default_random_engine generator;
  
  for (int i = 0 ; i < nb_object ; i++){
    std::uniform_real_distribution<float> distribution(_vertexs.front()._x
      ,_vertexs.back()._x);
    xRand = distribution(generator);

    y1 = calculateY(_vertexs.front(),_vertexs.back(),xRand);

    if ((_vertexs.front()._x < xRand) && (xRand < _vertexs[1]._x)){
      y2 = calculateY(_vertexs.front(),_vertexs[1],xRand);
    }
    if ((_vertexs[1]._x < xRand) && (xRand < _vertexs.back()._x)) {
      y2 = calculateY(_vertexs[1],_vertexs.back(),xRand);
    }

    if (y1 < y2){
      std::uniform_real_distribution<float> distribution2(y1,y2);
      yRand = distribution2(generator);
    }
    else {
      std::uniform_real_distribution<float> distribution2(y2,y1);
      yRand = distribution2(generator);
    }
    
    hex::Axial position = hex::Axial(xRand,yRand);
    _objects.push_back(position);
  }
}


float ZoneGenerator::calculateY(hex::Axial posA, hex::Axial posB, float xC){
  float y,a,b,c;
  
  b = -(posB._x - posA._x);
  a = posB._y - posA._y;
  c = - ((a * posA._x) + (b * posA._y));
  y = (-(a * xC + c)) / b;

  return y;
}


ZoneGenerator::Zone ZoneGenerator::objects(){
  return _objects;
}

ZoneGenerator::Zone ZoneGenerator::vertexs(){
  return _vertexs;
}