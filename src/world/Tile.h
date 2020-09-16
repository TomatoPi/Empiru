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

#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <unordered_set>

#include "utils/hex/HexCoords.h"
#include "entity/Peon.h"

/// \todo Abstraire les objets sur la map pour la rendre générique
///   et la découpler de son contenu
class Tile {
public:
  
  typedef std::unordered_set<Peon*> Content;
private :
  // Des trucs mais probablement :
  FlatHexPosition _pos;
  Content _content;
  
public:
  
  Tile(FlatHexPosition pos);
  Tile(FlatHexPosition pos,Peon* pitou);
  
  const FlatHexPosition & pos() const;
  
  void insert(Peon* pitou);
  void erase(Peon *p);
  
  bool isEmpty() const;

  const Content & getContent() const;
 
  std::string toString() const;
};
  

#endif /* WORLDOBJECT_H */
