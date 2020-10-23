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
#include "PeonEntity.h"

namespace peon {
  /// \brief Constructor
  /// \throw runtime_error on failure
  PeonRenderer::PeonRenderer(
            const gui::ObjectAsset& assets, 
            const SheetsPaths & args, 
            SDL_Renderer *rdr) :
    _sheet(assets._sheet),
    _mask(assets._mask),
    _select(assets._select),
    _whareh(SpriteSheet::loadFromFile(args.whareh_sheet, 1, 6, rdr)),
    _notify(SpriteSheet::loadFromFile(args.notify_sheet, 1, 2, rdr))
  {
  }

  /// \brief Draw a peon on screen, with (x,y) coordinate of bottom's middle
  void PeonRenderer::renderAt(
      const core::Pointer& obj, 
      int ori, int x, int y,
      const hex::Viewport & view)
  {
    const PEntity& peon(static_cast<const PEntity&>(*obj));
    const PeonSprite& datas(peon.get<PeonSprite>());
    int frame = datas._anim.value();
    ori = (ori + 6 - peon.get<WorldObject>().orientation()) % 6;
    SDL_Rect r;
    r.w = _sheet->width();
    r.h = _sheet->height();
    r.x = x - r.w / 2;
    r.y = y - r.h;
    if (datas._select) {
      _select->renderFrame(frame, ori, &r);
  //    if (const WorldPtr& ref = peon.attachtedWharehouse()) {
  //      const WorldObject & obj(*ref);
  //      int x, y;
  //      view.toPixel(obj.pos(), &x, &y);
  //      SDL_Rect r;
  //      r.w = _whareh->width();
  //      r.h = _whareh->height();
  //      r.x = x - r.w / 2;
  //      r.y = y - r.h - 70;
  //      _whareh->renderFrame(0, datas._wanim.tick(), &r);
  //    }
    }
  //  if (peon.isPaused()) {
  //    SDL_Rect r;
  //    r.w = _notify->width();
  //    r.h = _notify->height();
  //    r.x = x - r.w / 2 - 1;
  //    r.y = y - r.h - _sheet->height() + 9;
  //    _notify->renderFrame(0, datas._notanim.tick(), &r);
  //  }
    _sheet->renderFrame(frame, ori, &r);
  }

  /// \brief Draw a peon on screen, with (x,y) coordinate of bottom's middle
  void PeonRenderer::renderAt(
      const core::Pointer& obj, 
      int ori, int x, int y,
      const hex::Viewport & view,
      const SDL_Color & c)
  {
    const PEntity& peon(static_cast<const PEntity&>(*obj));
    const PeonSprite& datas(peon.get<PeonSprite>());
    int frame = datas._anim.value();
    ori = (ori + 6 - peon.get<WorldObject>().orientation()) % 6;
    SDL_Rect r;
    r.w = _mask->width();
    r.h = _mask->height();
    r.x = x - r.w / 2;
    r.y = y - r.h;
    _mask->setColorMod(c);
    _mask->renderFrame(frame, ori, &r);
  }
}