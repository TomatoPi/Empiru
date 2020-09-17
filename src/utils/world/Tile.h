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

#ifndef TILE_H
#define TILE_H

#include <unordered_set>

#include "utils/hex/HexCoords.h"
#include "utils/world/WorldObject.h"

class Tile {
public:
  
  /// \brief Tile's sub container
  typedef std::unordered_set<WorldObject*> Content;
  
private :
  
  Content _content;
  
public:
  
  Tile();
  
  void insert(WorldObject * obj);
  void erase(WorldObject * obj);
  
  bool isEmpty() const;

  const Content & getContent() const;
  Content & getContent();
};
  

#endif /* TILE_H */
