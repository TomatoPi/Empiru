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
/// \date 11 septembre 2020, 02:27
///

#include "SmallObjectRenderer.h"

/// Constructor
SmallObjectRenderer::SmallObjectRenderer(SpriteSheet *s) : AbstractRenderer(s) {
  
}

/// \brief Draw a peon on screen, with (x,y) coordinate of bottom's middle
int SmallObjectRenderer::renderAt(int x, int y, SDL_Renderer *rdr) {
  SDL_Rect r;
  r.w = _sheet->width();
  r.h = _sheet->height();
  r.x = x - r.w / 2;
  r.y = y - r.h;
  return _sheet->renderFrame(0, rdr, &r);
}
