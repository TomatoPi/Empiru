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
/// \file   PeonRenderer.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 16 septembre 2020, 12:48
/// \brief Provide PeonRenderer Object
///

#include <cassert>

#include "PeonRenderer.h"
#include "entity/peon/Peon.h"
#include "utils/gui/assets/SpriteAsset.h"

/// \brief Constructor
/// \throw runtime_error on failure
PeonRenderer::PeonRenderer(
    const SheetsPaths & args, 
    SDL_Renderer *rdr, 
    SDL_Renderer *mrdr) : 
  _sheet(SpriteAsset::loadFromFile(args.peon_sheet, rdr)),
  _mask(SpriteAsset::loadFromFile(args.mask_sheet, mrdr)),
  _select(SpriteAsset::loadFromFile(args.select_sheet, rdr)),
  _targets()
{
}

/// \brief Draw a peon on screen, with (x,y) coordinate of bottom's middle
void PeonRenderer::renderAt(
    const WorldRef * obj, 
    int ori, int x, int y,
    const hex::Viewport & view,
    SDL_Renderer *rdr)
{
  const Peon & peon(static_cast<const Peon &>(**obj));
  Datas & datas(_targets.at(obj));
  int frame = peon.hasOrders() ? datas._anim.update() : datas._anim.restart();
  ori = (ori + 6 - peon.direction().orientation()) % 6;
  SDL_Rect r;
  r.w = _sheet->width();
  r.h = _sheet->height();
  r.x = x - r.w / 2;
  r.y = y - r.h;
  if (datas._select) {
    _select->renderFrame(frame, ori, rdr, &r);
  }
  _sheet->renderFrame(frame, ori, rdr, &r);
}

/// \brief Draw a peon on screen, with (x,y) coordinate of bottom's middle
void PeonRenderer::renderAt(
    const WorldRef * obj, 
    int ori, int x, int y,
    const hex::Viewport & view,
    SDL_Renderer *rdr,
    const SDL_Color & c)
{
  const Peon & peon(static_cast<const Peon &>(**obj));
  Datas & datas(_targets.at(obj));
  int frame = peon.hasOrders() ? datas._anim.frame() : 0;
  ori = (ori + 6 - peon.direction().orientation()) % 6;
  SDL_Rect r;
  r.w = _mask->width();
  r.h = _mask->height();
  r.x = x - r.w / 2;
  r.y = y - r.h;
  _mask->setColorMod(c);
  _mask->renderFrame(frame, ori, rdr, &r);
}

/// \brief Called when a new object associated with this renderer is created
///  may instanciate fine scope datas, like animation state
void PeonRenderer::addTarget(const WorldRef *obj) noexcept {
  auto insert(_targets.emplace(obj, Datas()));
  assert(insert.second);
}
/// \brief Called when an object associated with this renderer is destroyed
///  may dealocate corresponding datas
void PeonRenderer::removeTarget(const WorldRef *obj) noexcept {
  auto itr(_targets.find(obj));
  assert(itr != _targets.end());
  _targets.erase(itr);
}
/// \brief Called when an object associated with this renderer is selected
///  may remember draw a special overlay around it
void PeonRenderer::targetSelected(const WorldRef * obj) {
  _targets.at(obj)._select = true;
}
/// \brief Called when an object associated with this renderer is deselected
///  may remember to stop draw special overlay
void PeonRenderer::targetDeselected(const WorldRef * obj) {
  _targets.at(obj)._select = false;
}