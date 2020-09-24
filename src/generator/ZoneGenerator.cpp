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
#include <random>
#include <algorithm>

ZoneGenerator::ZoneGenerator() : _vertexs(), _objects() {
  
}

void ZoneGenerator::createZone(int size) {
  for (int i = 0 ; i < size ; i++){
    hex::Axial position = hex::Axial((rand()%8),(rand()%8));
    _vertexs.push_back(position);
  }
}

void ZoneGenerator::addObject() {
  int nb_object = rand()%20;
  
  auto res = std::minmax_element(_vertexs.begin(), _vertexs.end(),
  [&]
  (const hex::Axial & a, const hex::Axial & b) -> bool {
    return a._x < b._x;
  });
  /*
  std::default_random_engine generator;
  std::uniform_real_distribution<float> distribution(res.first,res.second);
  
  for (int i = 0 ; i < nb_object ; i++){
    FlatHexPosition position = FlatHexPosition(distribution(generator), ...
        ,FlatHexPosition::Axial);
    // /!\ aux doublons
    _objects.push_back(position);
    
  }
   */
}


float ZoneGenerator::calculateY(hex::Axial posA, hex::Axial posB, float xC){
  float y,x,a,b,c;
  
  b = -(posB._x - posA._x);
  a = posB._y - posA._y;
  c = - ((a * posA._x) + (b * posA._y));
  y = (-(a * xC + c)) / b;

  return y;
}