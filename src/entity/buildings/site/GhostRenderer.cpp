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
/// \file   GhostRenderer.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 5 octobre 2020, 23:52
///

#include "GhostRenderer.h"
#include "entity/buildings/site/ConstructionGhost.h"
#include "utils/log.h"

/// \brief Render the object at given position
/// \param obj : the object beeing rendered
/// \param ori : curent camera's orientation
/// \param x   : object's x position on screen
/// \param y   : object's y position on screen
/// \param view: rendering viewport
/// \param rdr : renderer
/// \throw runtime_error on failure
void GhostRenderer::renderAt(
  const WorldPtr& obj, 
  int ori, int x, int y,
  const hex::Viewport & view)
{
  const ConstructionGhost& ghost(static_cast<const ConstructionGhost&>(*obj));
  gui::ObjectAsset asset(gui::TypedRegister::Get().getAsset(ghost.type()));
  bool& valid(_targets.at(obj));
  auto& sheet(asset._ghost);
  SDL_Rect rect;
  _blitter(&rect,
      sheet->width(), sheet->height(), 
      view.tileWidth(), view.tileHeight(), 
      x, y);
  if (valid != ghost.valid()) {
    uint8_t val(ghost.valid() ? 255 : 0);
    sheet->setColorMod(SDL_Color{255, val, val, 255});
    valid = ghost.valid();
  }
  sheet->renderFrame(0, ori, &rect);
}
  
/// \brief Called when a new object associated with this renderer is created
///  may instanciate fine scope datas, like animation state
void GhostRenderer::addTarget(const WorldPtr& obj) noexcept {
  auto insert(_targets.emplace(obj, false));
  LOG_DEBUG("Pouet\n");
  assert(insert.second);
}
/// \brief Called when an object associated with this renderer is destroyed
///  may dealocate corresponding datas
void GhostRenderer::removeTarget(const WorldPtr& obj) noexcept {
  auto itr(_targets.find(obj));
  assert(itr != _targets.end());
  _targets.erase(itr);
}