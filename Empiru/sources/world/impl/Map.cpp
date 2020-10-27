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

/// 
/// \file   World.cpp
/// \author CHARAMOND Lucien <lucien.charamond@outlook.fr>
///
/// \date 10 septembre 2020, 14:34
///
#include "Map.h"

#include "../IAllocator.h"

#include <hex/OddQ.h>
#include <hex/Conversion.h>

#include <cassert>

namespace world {
namespace impl {

/// \brief Constructor
/// \param mapHeight : Height of the map (number of hexs)
/// \param mapWidth : Width of the map (number of hexs)
Map::Map(std::size_t mapWidth, std::size_t mapHeight) :
    _mapWidth(mapWidth), _mapHeight(mapHeight), _map() {
  /* subscribe to object created events */
  IAllocator::Get().Subject<Events::ObjectCreated>::addSubscriber( // @suppress("Method cannot be resolved")
      [this](IAllocator&, Events::ObjectCreated &event) -> void {
        /* subscribe to created object movements */
        event.ptr->Object::Subject<Events::ObjectMoved>::addSubscriber( // @suppress("Method cannot be resolved")
            [this](Object &obj, Events::ObjectMoved &event) -> void {
              if (event.oldp.tile() != event.newp.tile()) {
                this->removeObject(obj.ptr(), event.oldp);
                this->addObject(obj.ptr(), event.newp);
              }
            });
        /* subscribe to created object destruction */
        event.ptr->Object::Subject<Events::ObjectDiscarded>::addSubscriber( // @suppress("Method cannot be resolved")
            [this](Object &obj, Events::ObjectDiscarded&) -> void {
              this->removeObject(obj.ptr());
            });
        /* add object to the map */
        this->addObject(event.ptr);
      });
}

/// \brief Must add given object to the world
void Map::addObject(const Object::Pointer &ptr) noexcept {
  addObject(ptr, ptr->pos());
}
void Map::addObject(const Object::Pointer &ptr, const Position &pos) noexcept {
  auto itr(_map.find(pos));
  if (itr == _map.end()) {
    itr = _map.emplace(pos, Tile()).first;
  }
  itr->second.insert(ptr);
}

/// \brief Must remove given object fro the world
void Map::removeObject(const Object::Pointer &ptr) noexcept {
  removeObject(ptr, ptr->pos());
}
void Map::removeObject(const Object::Pointer &ptr, const Position &pos) noexcept {
  auto itr(_map.find(pos));
  assert(itr != _map.end());
  itr->second.erase(ptr);
  if (itr->second.isEmpty()) {
    _map.erase(itr);
  }
}

/// \brief Must return tile content at given pos, or null if empty
const Tile::Content* Map::getContentAt(const Position &pos) const {
  auto itr(_map.find(pos));
  if (itr != _map.end()) {
    return &itr->second.getContent();
  }
  return nullptr;
}

/// \brief Must return true if given pos is on the map
bool Map::isOnMap(const Position &pos) const {
  hex::Grid grd(hex::toGrid(pos));
  // Easy case
  if (0 < grd._x && 0 < grd._y && grd._x < _mapWidth * 3 - 1
      && grd._y < _mapHeight * 2 - 1) {
    return true;
  }
  hex::OddQ off(hex::toOddQ(pos.tile()));
  return 0 <= off._x && 0 <= off._y && off._x < _mapWidth && off._y < _mapHeight;
}

/// \brief Return true if given position is valid
///   if position is invalid, return false and return pointer to the obstacle
///   in 'obstacle' if relevant
bool Map::tryPosition(const Position &newpos, const Object::Pointer &ptr,
    Object::Pointer *obstacle) const noexcept {
  const Object &object(*ptr);
  // Check validity
  if (!isOnMap(object.pos())) {
    return false;
  }
  // Check collisions
  bool valid(true);
  newpos.mapNeightbours([&](const Position &pos) -> bool { // @suppress("Invalid arguments")
    auto content = getContentAt(pos);
    if (content != nullptr) {
      for (auto obj : *content) {
        if (obj == ptr)
          continue;
        if (obj->collide(object, newpos)) {
          *obstacle = obj;
          valid = false;
          return true;
        }
      }
    }
    return false;
  });
  return valid;
}

} /* namespace impl */
} /* world namespace */
