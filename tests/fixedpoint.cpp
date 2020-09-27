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
 * File:   fixedpoint.cpp
 * Author: DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 *
 * Created on 26 septembre 2020, 13:06
 */

#include <cstdlib>
#include <iostream>
#include <random>
#include <functional>
#include <cfenv>

#include "utils/chrono.hpp"
#include "utils/log.h"
#include "utils/math/Math.h"

#define N (1L << 20)
#define DRY 2
#define WET (1L << 6)

template <typename T, typename Distribution>
void perfadd(const char * msg) {
  
  T array[N];
  Distribution dis(-100.0, 100.0);
  std::random_device rd;
  std::mt19937 gen(rd());
  T r(0);
  for (size_t i = 0; i < N ; ++i) array[i] = dis(gen);
  
  for (size_t run=0 ; run<DRY ; ++run) {
    for (size_t i=0 ; i<N ; ++i)
      r += array[i];
  }
  Chrono chrono;
  chrono.start();
  for (size_t run=0 ; run<WET ; ++run) {
    for (size_t i=0 ; i<N-1 ; ++i)
      r += array[i];
  }
  chrono.stop();
  LOG_INFO("%s[%s] : %fs -> %fs/call %d\n", 
      msg, typeid(T).name(), 
      chrono.timeSpan(), chrono.timeSpan()/(WET*N), *(int*)&r);
}
template <typename T, typename Distribution>
void perfsub(const char * msg) {
  
  T array[N];
  Distribution dis(-100.0, 100.0);
  std::random_device rd;
  std::mt19937 gen(rd());
  T r(0);
  for (size_t i = 0; i < N ; ++i) array[i] = dis(gen);
  
  for (size_t run=0 ; run<DRY ; ++run) {
    for (size_t i=0 ; i<N ; ++i)
      r -= array[i];
  }
  Chrono chrono;
  chrono.start();
  for (size_t run=0 ; run<WET ; ++run) {
    for (size_t i=0 ; i<N-1 ; ++i)
      r -= array[i];
  }
  chrono.stop();
  LOG_INFO("%s[%s] : %fs -> %fs/call %d\n", 
      msg, typeid(T).name(), 
      chrono.timeSpan(), chrono.timeSpan()/(WET*N), *(int*)&r);
}


template <typename T, typename Distribution>
void perfmult(const char * msg) {
  
  T array[N];
  Distribution dis(-100.0, 100.0);
  std::random_device rd;
  std::mt19937 gen(rd());
  T r(1);
  for (size_t i = 0; i < N ; ++i) array[i] = dis(gen);
  
  for (size_t run=0 ; run<DRY ; ++run) {
    for (size_t i=0 ; i<N ; ++i)
      r *= array[i];
  }
  Chrono chrono;
  chrono.start();
  for (size_t run=0 ; run<WET ; ++run) {
    for (size_t i=0 ; i<N-1 ; ++i)
      r *= array[i];
  }
  chrono.stop();
  LOG_INFO("%s[%s] : %fs -> %fs/call %d\n", 
      msg, typeid(T).name(), 
      chrono.timeSpan(), chrono.timeSpan()/(WET*N), *(int*)&r);
}


template <typename T, typename Distribution>
void perfdiv(const char * msg) {
  
  T array[N];
  Distribution dis(1, 100.0);
  std::random_device rd;
  std::mt19937 gen(rd());
  T r(10000000);
  for (size_t i = 0; i < N ; ++i) array[i] = dis(gen);
  
  for (size_t run=0 ; run<DRY ; ++run) {
    for (size_t i=0 ; i<N ; ++i)
      r /= array[i];
  }
  Chrono chrono;
  chrono.start();
  for (size_t run=0 ; run<WET ; ++run) {
    for (size_t i=0 ; i<N-1 ; ++i)
      r /= array[i];
  }
  chrono.stop();
  LOG_INFO("%s[%s] : %fs -> %fs/call %d\n", 
      msg, typeid(T).name(), 
      chrono.timeSpan(), chrono.timeSpan()/(WET*N), *(int*)&r);
}



int main(int argc, char** argv) {
  
  perfadd<float,std::uniform_real_distribution<>>("+");
  perfadd<int,std::uniform_int_distribution<>>("+");
  
  perfsub<float,std::uniform_real_distribution<>>("-");
  perfsub<int,std::uniform_int_distribution<>>("-");
  
  perfmult<float,std::uniform_real_distribution<>>("*");
  perfmult<int,std::uniform_int_distribution<>>("*");
  
  perfdiv<float,std::uniform_real_distribution<>>("/");
  perfdiv<int,std::uniform_int_distribution<>>("/");

  return (EXIT_SUCCESS);
}

