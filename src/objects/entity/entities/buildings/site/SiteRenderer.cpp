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
/// \file   SiteRenderer.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 6 octobre 2020, 12:03
///
#if 0
#include "SiteRenderer.h"
#include "ConstructSite.h"

SiteRenderer::SiteRenderer(const gui::ObjectAsset& asset) noexcept :
  _sheet(asset._sheet), _mask(asset._mask), _blitter()
{
}

/// \brief Draw the object at given position
void SiteRenderer::renderAt(
  const WorldPtr& obj, 
  int ori, int x, int y,
  const hex::Viewport & view)
{
  const ConstructionSite& site(static_cast<const ConstructionSite&>(*obj));
  int frame = std::min(site.progress() / 25, 3);
  SDL_Rect r;
  _blitter(&r, 
    _sheet->width(), _sheet->height(), 
    view.tileWidth(), view.tileHeight(), 
    x, y);
  _sheet->renderFrame(frame, ori, &r);
}

/// \brief Render the object at given position, replacing the texture with
///   'color'
void SiteRenderer::renderAt(
  const WorldPtr& obj,
  int ori, int x, int y,
  const hex::Viewport & view,
  const SDL_Color & c)
{
  const ConstructionSite& site(static_cast<const ConstructionSite&>(*obj));
  int frame = std::min(site.progress() / 25, 3);
  SDL_Rect r;
  _blitter(&r, 
    _mask->width(), _mask->height(), 
    view.tileWidth(), view.tileHeight(), 
    x, y);
  _mask->setColorMod(c);
  _mask->renderFrame(frame, ori, &r);
}
#endif