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

/// 
/// \file   chrono.hpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 16 septembre 2020, 01:40
///

#ifndef CHRONO_HPP
#define CHRONO_HPP

#include <chrono>

class Chrono
{
public:
  void start() { 
      begin = std::chrono::high_resolution_clock::now(); 
  }
  void stop() { 
      end = std::chrono::high_resolution_clock::now(); 
  }
  double timeSpan() const { 
      return (std::chrono::duration_cast<std::chrono::duration<double>>(end - begin)).count();  
  }

private:
  std::chrono::high_resolution_clock::time_point begin;
  std::chrono::high_resolution_clock::time_point end;
};


#endif /* CHRONO_HPP */

