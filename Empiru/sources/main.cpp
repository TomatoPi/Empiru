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
/// \file   main.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 27 oct. 2020 01:15:20
///
#include "world/impl/Map.h"
#include "world/impl/Allocator.h"

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

namespace {
constexpr std::size_t SIZE = 8;
}

int main(int argc, char **argv) {

  world::IAllocator::registerAllocator(new world::impl::Allocator());
  world::impl::Map _worldMap(SIZE, SIZE);

  return 0;
}
