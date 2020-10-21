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
/// \file   Tile.h
/// \author CHARAMOND Lucien <lucien.charamond@outlook.fr>
///
/// \date 10 septembre 2020, 13:49
///

#ifndef WORLD_TILE_H
#define WORLD_TILE_H

#include "engine/core/Pointer.h"
#include <cassert>
#include <unordered_set>

/// \brief Tiles are world's container
class Tile {
public:
  
  /// \brief Tile's sub container
  typedef std::unordered_set<core::Pointer,alloc::PtrHash,alloc::PtrEquals>
    Content;
  
private :
  
  Content _content; ///< Tile's content
  
public:
  
  /// \brief Constructor
  Tile() noexcept : 
    _content() 
  {
  }
  /// \brief Default copy constructor
  Tile(const Tile &) = default;
  /// \brief Default assignment copy
  Tile & operator= (const Tile &) = default;
  /// \brief Default destructor
  ~Tile() = default;
  
  /// \brief Add given object to the tile
  void insert(const core::Pointer& ptr) noexcept {
    bool success(_content.insert(ptr).second);
    assert(success);
  }
  /// \brief Remove given object from the tile
  void erase(const core::Pointer& ptr) noexcept {
    bool success(_content.erase(ptr));
    assert(success);
  }
  
  /// \brief return true if there is nothing on the tile
  bool isEmpty() const noexcept {
    return 0 == _content.size();
  }

  /// \brief return tile's content
  const Content & getContent() const noexcept {
    return _content;
  }
};

#endif /* WORLD_TILE_H */
