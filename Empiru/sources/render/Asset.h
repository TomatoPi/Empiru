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
/// \file   Asset.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 27 oct. 2020 16:27:23
///
#ifndef SOURCES_RENDER_ASSET_H_
#define SOURCES_RENDER_ASSET_H_

#include <uid/uid.h>
#include <sprite/SpriteSheet.h>
#include <typeinfo>

namespace render {

struct Asset {
  std::shared_ptr<SpriteSheet> sheet;
  std::shared_ptr<SpriteSheet> mask;
  std::shared_ptr<SpriteSheet> select;
  Asset(std::shared_ptr<SpriteSheet> sheet, std::shared_ptr<SpriteSheet> mask,
      std::shared_ptr<SpriteSheet> select) noexcept :
      sheet(sheet), mask(mask), select(select) {
  }
};

using AssetUIDGen = uid::UIDGenerator;
using AssetUID = AssetUIDGen::UID;

}  // namespace render

#endif /* SOURCES_RENDER_ASSET_H_ */
