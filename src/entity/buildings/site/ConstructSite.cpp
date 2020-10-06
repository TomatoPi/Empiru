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
/// \file   ConstructSite.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 30 septembre 2020, 11:20
///

#include "ConstructSite.h"

ConstructionSite::ConstructionSite() : 
  WorldObject(WorldObject::SHollow),
  _workers(),
  _progress(0), _cptr(0), _difficulty(0)
{  
}

int ConstructionSite::progress() const noexcept {
  return _progress;
}
bool ConstructionSite::isFinished() const noexcept {
  return _progress >= 100;
}
void ConstructionSite::progressTick(int speed) {
  int tmp(_cptr + speed);
  _progress += tmp / _difficulty;
  _cptr = tmp % _difficulty;
}

void ConstructionSite::addWorker(const WorldPtr& ptr) {
  bool success(_workers.emplace(ptr).second);
  assert(success);
}
void ConstructionSite::removeWorker(const WorldPtr& ptr) {
  bool success(_workers.erase(ptr));
  assert(success);
}
const ConstructionSite::WorkersList& ConstructionSite::workers() const noexcept {
  return _workers;
}