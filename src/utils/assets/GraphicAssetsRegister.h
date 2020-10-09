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
/// \file   GraphicAssetsRegister.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 30 septembre 2020, 16:01
///

#ifndef GRAPHICASSETSREGISTER_H
#define GRAPHICASSETSREGISTER_H

#include <string>
#include "utils/assets/AssetManager.h"
#include "utils/assets/SpriteSheet.h"

namespace gui {
  
  struct ObjectAsset {
    
    enum Sheet {
      ReqSheet =0x01,
      ReqMask  =0x02,
      ReqSelect=0x04,
      ReqGhost =0x08,
    };
    
    ObjectAsset(
            const std::string &path,
            Sheet requireds,
            SDL_Renderer* rdr,
            SDL_Renderer* mrdr);
    
    std::shared_ptr<SpriteSheet> _sheet;
    std::shared_ptr<SpriteSheet> _mask;
    std::shared_ptr<SpriteSheet> _select;
    std::shared_ptr<SpriteSheet> _ghost;
  };
  
  inline ObjectAsset::Sheet 
  operator| (ObjectAsset::Sheet a, ObjectAsset::Sheet b) {
    return static_cast<ObjectAsset::Sheet>(
            static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
  }
  
  class TypedRegister : public AssetManager<ObjectAsset, TypedRegister> {};
}

#endif /* GRAPHICASSETSREGISTER_H */
