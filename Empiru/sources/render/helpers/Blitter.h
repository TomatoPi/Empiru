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
/// \file   Blitter.h
/// \author tomato
///
/// \date 29 oct. 2020 04:13:34
///
#ifndef SOURCES_RENDER_HELPERS_BLITTER_H_
#define SOURCES_RENDER_HELPERS_BLITTER_H_

#include <gui/Pixel.h>
#include <SDL2/SDL_rect.h>

namespace render {

namespace helpers {

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
struct OnTileBlitter {
  SDL_Rect operator()(const gui::Pixel &pos, const gui::Pixel &size,
      const gui::Pixel &tile) const noexcept {
    return SDL_Rect { .x = (pos._x - size._x / 2), .y = (pos._y + tile._y / 2
        - size._y), .w = size._x, .h = size._y };
  }
};

/// \brief Put the rectangle 'r' as if (x,y) was object foot's position
/// \see void blitTile(SDL_Rect * r, int w, int h, int tw, int th, int x, int y)
struct OnFootBlitter {
  SDL_Rect operator()(const gui::Pixel &pos, const gui::Pixel &size,
      const gui::Pixel &tile) const noexcept {
    return SDL_Rect { .x = (pos._x - size._x / 2), .y = (pos._y - size._y), .w =
        size._x, .h = size._y };
  }
};

}  // namespace helpers

}  // namespace render

#endif /* SOURCES_RENDER_HELPERS_BLITTER_H_ */
