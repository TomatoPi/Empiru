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

#include <cassert>

#include "WorldMap.h"
#include "utils/hex/OddQ.h"
#include "utils/hex/Conversion.h"
#include "engine/events/GameEvents.h"
#include "objects/decorator/decorators/worldobj/WorldObject.h"

/// \brief Constructor
/// \param mapHeight : Height of the map (number of hexs)
/// \param mapWidth : Width of the map (number of hexs)
WorldMap::WorldMap(int mapWidth, int mapHeight) :
  _mapWidth(mapWidth),
  _mapHeight(mapHeight),
  _map()
{
  assert(0 < mapWidth);
  assert(0 < mapHeight);
  this->registerEvent<GameEvents::ObjectCreated>(
      [this](const GameEvents::ObjectCreated& event) -> void {
        if (typeid(*event._ptr) == typeid(WorldObject)) {
          this->addObject(event._ptr);
          event._ptr->subscribe(this->_this);
        }
      });
  this->registerEvent<GameEvents::ObjectDestroyed>(
      [this](const GameEvents::ObjectDestroyed& event) ->void {
        if (typeid(*event._ptr) == typeid(WorldObject)) {
          this->removeObject(event._ptr);
        }
      });
}

/// \brief Must add given object to the world
void WorldMap::addObject(const core::Pointer& ptr) noexcept {
  addObject(ptr, static_cast<const WorldObject&>(*ptr).pos());
}
void WorldMap::addObject(const core::Pointer& ptr, const world::Position& pos)
noexcept {
  auto itr(_map.find(pos));
  if (itr == _map.end()) {
    itr = _map.emplace(pos,Tile()).first;
  }
  itr->second.insert(ptr);
}

/// \brief Must remove given object fro the world
void WorldMap::removeObject(const core::Pointer& ptr) noexcept {
  removeObject(ptr, static_cast<const WorldObject&>(*ptr).pos());
}
void 
WorldMap::removeObject(const core::Pointer& ptr, const world::Position& pos) 
noexcept {
  auto itr(_map.find(pos));
  assert(itr != _map.end());
  itr->second.erase(ptr);
  if (itr->second.isEmpty()) {
    _map.erase(itr);
  }
}

/// \brief Must return tile content at given pos, or null if empty
const Tile::Content * WorldMap::getContentAt(const world::Position & pos) const {
  auto itr(_map.find(pos));
  if (itr != _map.end()){
    return &itr->second.getContent();
  }
  return nullptr;
}

/// \brief Must return true if given pos is on the map
bool WorldMap::isOnMap(const world::Position & pos) const {
  hex::Grid grd(hex::toGrid(pos));
  // Easy case
  if (0 < grd._x && 0 < grd._y 
    && grd._x < _mapWidth*3-1 && grd._y < _mapHeight*2-1) {
    return true;
  }
  hex::OddQ off(hex::toOddQ(pos.tile()));
  return 0 <= off._x && 0 <= off._y 
      && off._x < _mapWidth
      && off._y < _mapHeight;
}

/// \brief Return true if given position is valid
///   if position is invalid, return false and return pointer to the obstacle
///   in 'obstacle' if relevant
bool WorldMap::tryPosition(
  const world::Position& newpos, 
  const core::Pointer& ptr, 
  core::Pointer* obstacle) 
const noexcept
{
  // Check validity
  const WorldObject& object(static_cast<const WorldObject&>(*ptr));
  if (!isOnMap(object.pos())) {
    return false;
  }
  // Check collisions
  bool valid(true);
  newpos.mapNeightbours(
    [&] (const world::Position & pos) -> bool {
      auto content = getContentAt(pos);
      if (content != nullptr){
        for (auto obj : *content){
          if (obj == ptr) 
            continue;
          const WorldObject& tmp(static_cast<const WorldObject&>(*obj));
          if (tmp.collide(object, newpos)) {
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

/// \brief Must be called on events
void doOnNotify(const core::Pointer& p, const core::Object::Event& e) noexcept {
  if (typeid(e) == typeid(WorldObject::Event)) {
    const WorldObject& obj(static_cast<const WorldObject&>(*p));
    const WorldObject::Event& event(static_cast<const WorldObject::Event&>(e));
    if (event.type == WorldObject::Event::Type::Moved) {
      /* if object's tile has changed move it */
      if (event.old.tile() != obj.pos().tile()) {
        map.removeObject(p, event.old);
        map.addObject(p);
      }
    }
  }
}