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
 * File:   roundopti.cpp
 * Author: DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 *
 * Created on 16 septembre 2020, 01:39
 */

#include <cstdlib>
#include <iostream>
#include <random>
#include <functional>
#include <cfenv>

#include "utils/chrono.hpp"
#include "utils/log.h"
#include "utils/math/Math.h"

#define N (1 << 20)
#define DRY 2
#define WET 5

int control(float a) {
  return std::roundf(a);
}

void perf(const char *msg, std::function<int(float)> func, float * array) {
  for (size_t run=0 ; run<DRY ; ++run) {
    for (size_t i=0 ; i<N ; ++i)
      func(array[i]);
  }
  Chrono chrono;
  chrono.start();
  for (size_t run=0 ; run<WET ; ++run) {
    for (size_t i=0 ; i<N ; ++i)
      func(array[i]);
  }
  chrono.stop();
  LOG_INFO("%s : %fs -> %fs/call\n", msg, chrono.timeSpan(), chrono.timeSpan()/(WET*N));
}

void check(
  const char *msg, 
  std::function<int(float)> f, 
  std::function<int(float)> h, 
  float * array)
{
  for (size_t i=0 ; i<N ; ++i) {
    if (f(array[i]) != h(array[i])) {
      LOG_WRN("%s : %lu : %f -> (%d,%d)\n", 
          msg, i, array[i], f(array[i]), h(array[i]));
      return;
    }
  }
  LOG_INFO("%s : Check ok\n", msg);
}

int main(int argc, char** argv) {
  
  float array[N];
  std::uniform_real_distribution<> dis(-100.0, 100.0);
  std::random_device rd;
  std::mt19937 gen(rd());
  array[0] = -0.5;
  array[1] = 0.5;
  array[2] = -1.5;
  array[3] = 1.5;
  for (size_t i = 4; i < N ; ++i) array[i] = dis(gen);
  
  perf("std     ", control, array);
  perf("mrnd    ", math::mrnd, array);
  perf("fastmrnd", math::fastmrnd, array);
  perf("fastmrnd2", math::fastmrnd2, array);
  
  check("mrnd vs fast         ", math::mrnd, math::fastmrnd, array);
  check("fastmrnd vs fastmrnd2", math::fastmrnd, math::fastmrnd2, array);

  return (EXIT_SUCCESS);
}

