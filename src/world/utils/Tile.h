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
/// \file   WorldObject.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 10 septembre 2020, 13:49
///

#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <vector>

#include "utils/hex/HexCoords.h"
#include "entity/peon.h"


class Tile {
private :
  // Des trucs mais probablement :
  FlatHexPosition _pos;
  std::vector<Peon*> _entity_vector;
  
public:
  
  Tile(FlatHexPosition pos);
  Tile(FlatHexPosition pos,Peon* pitou);
  
  const FlatHexPosition & pos() const;
  
 void insert(Peon* pitou);
  
  std::string toString() const;
};
  

#endif /* WORLDOBJECT_H */
