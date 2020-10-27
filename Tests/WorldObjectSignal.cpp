/*
 * Copyright (C) 2020 tomato
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
/// \file   WorldObjectSignal.cpp
/// \author tomato
///
/// \date 27 oct. 2020 02:15:23
///
#include "world/Object.cpp"
#include <iostream>
#include <functional>

using namespace std;

void moved(world::Object &o, const world::Events::ObjectMoved &e) {
  cout << o.uid() << " : " << e.oldp << " -> " << e.newp << endl;
}
void rotated(world::Object &o, const world::Events::ObjectRotated &e) {
  cout << o.uid() << " : " << e.oldr << " -> " << e.newr << endl;
}

int main(int argc, char **argv) {
  world::Object a(0, world::Object::Size::Tile, world::Position(1, 1));
  world::Object b(1, world::Object::Size::Tile, world::Position(2, 1));

  auto k1 =
      a.SuperObserver::Subject<world::Object, world::Events::ObjectMoved>::addSubscriber(
          std::bind_front(moved));
  auto k2 =
      b.SuperObserver::Subject<world::Object, world::Events::ObjectRotated>::addSubscriber(
          std::bind_front(rotated));
  auto k3 =
      a.SuperObserver::Subject<world::Object, world::Events::ObjectRotated>::addSubscriber(
          std::bind_front(rotated));

  a.pos(world::Position(2, 2));
  b.pos(world::Position(3, 1));
  a.orientation(9);
  b.orientation(5);

  return 0;
}

