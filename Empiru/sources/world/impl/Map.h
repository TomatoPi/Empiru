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

#include <unordered_map>

namespace world {
namespace impl {

/// \brief Object that handle Map and Objects
class Map final : public IMap {
public:

private:

  /// \brief Hollow Matrix
  typedef std::unordered_map<Position, Tile, Position::TileHasher,
      Position::TileEquals> ObjList;

  std::size_t _mapWidth;  ///< Horizontal tile count
  std::size_t _mapHeight; ///< Verical tile count
  ObjList _map;   ///< Hollow matrix of world content

public:

  /// \brief Constructor
  /// \param mapHeight : Height of the map (number of hexs)
  /// \param mapWidth : Width of the map (number of hexs)
  Map(std::size_t mapWidth, std::size_t mapHeight);
  virtual ~Map() noexcept = default;

  /// \brief Must return tile content at given pos, or null if empty
  const Tile::Content* getContentAt(const Position &pos) const override final;

  /// \brief Must return true if given pos is on the map
  bool isOnMap(const Position &pos) const override final;

  /// \brief Return true if given position is valid
  ///   if position is invalid, return false and return pointer to the obstacle
  ///   in 'obstacle' if relevant
  bool tryPosition(const Position &pos, const Object::Pointer &entity,
      Object::Pointer *obstacle) const noexcept override final;

private:

  void addObject(const Object::Pointer &ptr) noexcept;
  void addObject(const Object::Pointer &ptr, const Position &pos) noexcept;
  void removeObject(const Object::Pointer &ptr) noexcept;
  void removeObject(const Object::Pointer &ptr, const Position &pos) noexcept;
};

} /* namespace impl */
} /* world */

#endif /* WORLD_H*/
