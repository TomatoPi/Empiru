/*
 * Copyright (C) 2020 tomato
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
/// \file   AssetLoader.h
/// \author tomato
///
/// \date 29 oct. 2020 04:28:11
///
#ifndef SOURCES_RENDER_HELPERS_ASSETLOADER_H_
#define SOURCES_RENDER_HELPERS_ASSETLOADER_H_

#include "../Asset.h"

namespace render {

namespace helpers {

enum Sheet {
  ReqSheet = 0x01, ReqMask = 0x02, ReqSelect = 0x04, ReqGhost = 0x08,
};

inline Sheet operator|(Sheet a, Sheet b) noexcept {
  return static_cast<Sheet>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

std::shared_ptr<Asset> loadAsset(const std::string &path, Sheet requireds,
    SDL_Renderer *rdr, SDL_Renderer *mrdr);

}  // namespace helpers

}  // namespace render

#endif /* SOURCES_RENDER_HELPERS_ASSETLOADER_H_ */
