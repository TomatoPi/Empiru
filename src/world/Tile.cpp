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
/// \file   Tile.cpp
/// \author CHARAMOND Lucien <lucien.charamond@outlook.fr>
///
/// \date 10 septembre 2020, 13:49
///
#include <cassert>
#include "Tile.h"

Tile::Tile(FlatHexPosition pos) : 
  _pos(pos),
  _content()
{
}

Tile::Tile(FlatHexPosition pos, Peon *pitou) : 
  _pos(pos),
  _content()
{
  _content.insert(pitou);
}

const FlatHexPosition & Tile::pos() const {
  return _pos;
}


void Tile::insert(Peon *pitou){
  assert(_content.insert(pitou).second);
}
void Tile::erase(Peon *p) {
  assert(_content.erase(p));
}
  
bool Tile::isEmpty() const {
  return 0 == _content.size();
}

const Tile::Content & Tile::getContent() const{
  return _content;
}
 
std::string Tile::toString() const{
  std::string ts = "{";
  return ts.append(_pos.toString())
      .append("}");
}

