/*
 * Copyright (C) 2020 DAGO Kokri Esaïe <dago.esaie@protonmail.com>
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
 * File:   hexcoord.cpp
 * Author: DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 *
 * Created on 16 septembre 2020, 09:22
 */

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <random>
#include <functional>

#include "utils/hex/HexCoords.h"
#include "utils/chrono.hpp"
#include "utils/log.h"

#define N (1 << 16)
#define DRY 2
#define WET 5

FlatHexPosition & convert1(
  FlatHexPosition * pos, FlatHexPosition::System target) 
{
  if (target == pos->_type) {
    return *pos;
  }
  // Convert this position to Axial
  float x, y;
  switch (pos->_type) {
  case FlatHexPosition::OddQOffset :
    x = pos->_x;
    y = pos->_y - (pos->_x - ((int)pos->_x & 1)) / 2.;
    break;
  case FlatHexPosition::Axial :
  case FlatHexPosition::Cubic :
    x = pos->_x;
    y = pos->_y;
    break;
  case FlatHexPosition::Grid :
    x = pos->_x / 3.;
    y = pos->_y / 2. - pos->_x / 6.;
    break;
  default:
    assert(0);
  }
  // Convert from Axial to Target
  switch (target) {
  case FlatHexPosition::OddQOffset :
    pos->_x = x;
    pos->_y = y + (x - ((int)(x) & 1)) / 2.;
    pos->_z = 0;
    break;
  case FlatHexPosition::Axial :
    pos->_x = x;
    pos->_y = y;
    pos->_z = 0;
    break;
  case FlatHexPosition::Cubic :
    pos->_x = x;
    pos->_y = y;
    pos->_z = x - y;
    break;
  case FlatHexPosition::Grid :
    pos->_x = 3 * x;
    pos->_y = 2 * y + x;
    pos->_z = 0;
    break;
  default :
    assert(0);
  }
  // This is the end
  pos->_type = target;
  return *pos;
}

FlatHexPosition & convert2(
  FlatHexPosition * pos, FlatHexPosition::System target) 
{
  if (target == pos->_type) {
    return *pos;
  }
  // Convert this position to Axial
  switch (pos->_type) {
  case FlatHexPosition::OddQOffset :
    pos->_y = pos->_y - (pos->_x - ((int)pos->_x & 1)) / 2.;
    break;
  case FlatHexPosition::Axial :
  case FlatHexPosition::Cubic :
    break;
  case FlatHexPosition::Grid :
    pos->_y = pos->_y / 2. - pos->_x / 6.;
    pos->_x /= 3.;
    break;
  default:
    assert(0);
  }
  // Convert from Axial to Target
  switch (target) {
  case FlatHexPosition::OddQOffset :
    pos->_y = pos->_y + (pos->_x - ((int)(pos->_x) & 1)) / 2.;
    break;
  case FlatHexPosition::Axial :
    break;
  case FlatHexPosition::Cubic :
    pos->_z = pos->_x - pos->_y;
    break;
  case FlatHexPosition::Grid :
    pos->_y = 2 * pos->_y + pos->_x;
    pos->_x = 3 * pos->_x;
    break;
  default :
    assert(0);
  }
  // This is the end
  pos->_type = target;
  return *pos;
}

typedef std::function<FlatHexPosition&(FlatHexPosition*,FlatHexPosition::System)> Function;

void perf(
  const char *msg, 
  Function func, 
  FlatHexPosition * array, 
  FlatHexPosition::System * targets) 
{
  for (size_t run=0 ; run<DRY ; ++run) {
    for (size_t i=0 ; i<N ; ++i)
      func(array+i, targets[i]);
  }
  Chrono chrono;
  chrono.start();
  for (size_t run=0 ; run<WET ; ++run) {
    for (size_t i=0 ; i<N ; ++i)
      func(array+i, targets[i]);
  }
  chrono.stop();
  LOG_INFO("%s : %fs -> %fs/call\n", msg, chrono.timeSpan(), chrono.timeSpan()/(WET*N));
}

void check(
  const char *msg, 
  Function f, 
  Function h, 
  FlatHexPosition * array, 
  FlatHexPosition::System * targets)
{
  for (size_t i=0 ; i<N ; ++i) {
    if (f(array+i, targets[i]) != h(array+i, targets[i])) {
      LOG_WRN("%s : %lu : Failure\n", msg, i);
      return;
    }
  }
  LOG_INFO("%s : Check ok\n", msg);
}

int main(int argc, char** argv) {
  
  FlatHexPosition array[N];
  FlatHexPosition::System targets[N];
  
  std::uniform_int_distribution<> sys(0, 3);
  std::uniform_real_distribution<> dis(-100.0, 100.0);
  std::random_device rd;
  std::mt19937 gen(rd());
  
  for (size_t i=0 ; i<N ; ++i) {
    array[i] = FlatHexPosition(dis(gen), dis(gen), FlatHexPosition::Axial);
    targets[i] = static_cast<FlatHexPosition::System>(sys(gen));
  }
  
  perf("OutOfPlace", convert1, array, targets);
  perf("InPlace   ", convert2, array, targets);
  
  check("Check", convert1, convert2, array, targets);

  return (EXIT_SUCCESS);
}

