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
/// \file   GraphicAssetsRegister.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 30 septembre 2020, 16:02
///

#include "GraphicAssetsRegister.h"

namespace {
  
  /// \brief Load a sheet from given file and auto cut it in 6 colums
  ///   and squared sprites
  std::shared_ptr<SpriteSheet> 
  loadAndCut(const std::string& path, SDL_Renderer *rdr) {
    
    auto sheet(SpriteSheet::loadFromFile(path, 1, 1, rdr));
    int width(sheet->width() / 6), rows;
    rows = sheet->height() / width;
    sheet->recut(rows, 6);
    return sheet;
  }
  
  ///
  std::shared_ptr<SpriteSheet> 
  tryLoad(const std::string& path, bool required, SDL_Renderer* rdr) {
    
    if (required) {
      return loadAndCut(path, rdr);
    } else {
      return nullptr;
    }
  }
}

namespace gui {

  ObjectAsset::ObjectAsset(
            const std::string &path,
            Sheet requireds,
            SDL_Renderer* rdr,
            SDL_Renderer* mrdr) :
    _sheet(tryLoad(path + "_sheet.png", requireds & Sheet::ReqSheet, rdr)), 
    _mask(tryLoad(path + "_mask.png", requireds & Sheet::ReqMask, mrdr)), 
    _select(tryLoad(path + "_select.png", requireds & Sheet::ReqSelect, rdr))
  {
  }
}