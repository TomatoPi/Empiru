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
/// \file   AbstractRenderer.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 14 septembre 2020, 12:49
///

#include "AbstractRenderer.h"

/// \brief Put the rectangle 'r' as if (x,y) was tile's center coordinate
///
/// \param r  : return computed blit rectangle
///
/// \param w  : blit width
/// \param h  : blit height
///
/// \param tw : tile's width on screen
/// \param th : tile's height on screen
/// \param x  : tile's center x
/// \param y  : tile's center y
///
void TileBlitter::operator() (SDL_Rect * rect, 
    int w, int h, int tw, int th, int x, int y)
const {
  rect->w = w, rect->h = h;
  rect->x = x - rect->w/2;
  rect->y = y + th/2 - rect->h;
}

/// \brief Put the rectangle 'r' as if (x,y) was object foot's position
/// \see void blitTile(SDL_Rect * r, int w, int h, int tw, int th, int x, int y)
void FootBlitter::operator() (SDL_Rect * rect, 
    int w, int h, int tw, int th, int x, int y)
const {
  rect->w = w, rect->h = h;
  rect->x = x - rect->w/2;
  rect->y = y - rect->h;
}