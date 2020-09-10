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

/* 
 * File:   newsimpletest.cpp
 * Author: CHARAMOND Lucien <lucien.charamond@outlook.fr>
 *
 * Created on 10 septembre 2020, 15:03
 */

#include <stdlib.h>
#include <iostream>

#include "world/utils/World.h"


int main(int argc, char** argv) {
  World  world = World(10,10);
  Tile wo1 = Tile(FlatHexPosition());
  Tile wo3 = Tile(FlatHexPosition(12,45,FlatHexPosition::Axial));
  Tile wo4 = Tile(FlatHexPosition(1,1,FlatHexPosition::Axial));
  Tile wo5 =  Tile(FlatHexPosition(32,1.4,FlatHexPosition::Axial));
  world.addObject(wo1);
  printf(world.toString().c_str());
  return (EXIT_SUCCESS);
}

