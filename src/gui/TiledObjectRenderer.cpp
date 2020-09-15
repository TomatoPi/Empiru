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
/// \file   TiledObjectRenderer.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 14 septembre 2020, 13:33
///

#include "TiledObjectRenderer.h"

TiledObjectRenderer::TiledObjectRenderer(
  HexViewport *wv, SpriteSheet *sheet) :
  AbstractRenderer(sheet),
  _worldview(wv)
{
  
}

int TiledObjectRenderer::renderAt(int x, int y, SDL_Renderer *rdr) {
  SDL_Rect rect;
  rect.w = _sheet->width(), rect.h = _sheet->height();
  rect.x = x - rect.w/2;
  rect.y = y + _worldview->tileHeight()/2 - rect.h;
  return _sheet->renderFrame(0, 0, rdr, &rect);
}