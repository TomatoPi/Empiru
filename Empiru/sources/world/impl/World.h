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
/// \file   World.h
/// \author CHARAMOND Lucien <lucien.charamond@outlook.fr>
///
/// \date 10 septembre 2020, 14:35
///
#ifndef  WORLD_H
#define WORLD_H

#include "../IMap.h"
#include "../Position.h"
#include "../Tile.h"
#include "../Object.h"
#include "../IAllocator.h"

#include <alloc/impl/IndexAllocator.h>
#include <unordered_map>
#include <vector>

namespace world {
namespace impl {

/// \brief Object that handle Map and Objects
class World final : public IMap, public IAllocator {
public:

private:

  using _Allocator = alloc::IndexAllocator<Object, Object>;
  _Allocator _alloc;

  /// \brief Hollow Matrix
  using ObjList = std::unordered_map<Position, Tile, Position::TileHasher,
  Position::TileEquals>;
  using ObjTable = std::unordered_map<game::EUID, Object::Pointer>; // @suppress("Invalid template argument")
  using Garbage = std::vector<Object::Pointer>;

  std::size_t _mapWidth;  ///< Horizontal tile count
  std::size_t _mapHeight; ///< Verical tile count
  ObjList _map;   ///< Hollow matrix of world content
  ObjTable _objects;
  Garbage _garbage;

public:

  /// \brief Constructor
  /// \param mapHeight : Height of the map (number of hexs)
  /// \param mapWidth : Width of the map (number of hexs)
  World(std::size_t mapWidth, std::size_t mapHeight);
  virtual ~World() noexcept = default;

  Object::Pointer createObject(game::EUID entity, Object::Size s,
      const Position &p, float r, int o) override;

  void destroyGarbage() noexcept override;

  /// \brief Must return tile content at given pos, or null if empty
  const Tile::Content* getContentAt(const Position &pos) const override final;

  /// \brief Must return true if given pos is on the map
  bool isOnMap(const Position &pos) const override final;

  /// \brief Return true if given position is valid
  ///   if position is invalid, return false and return pointer to the obstacle
  ///   in 'obstacle' if relevant
  bool tryPosition(const Position &pos, const Object::Pointer &entity,
      Object::Pointer *obstacle) const noexcept override final;

  /// \brief return object associated with given entity
  Object& getObject(const game::EUID) noexcept override final;

private:

  void addObject(const Object::Pointer &ptr) noexcept;
  void addObject(const Object::Pointer &ptr, const Position &pos) noexcept;
  void removeObject(const Object::Pointer &ptr) noexcept;
  void removeObject(const Object::Pointer &ptr, const Position &pos) noexcept;
  void destroyObject(Object::Pointer ptr);
};

} /* namespace impl */
} /* world */

#endif /* WORLD_H*/
