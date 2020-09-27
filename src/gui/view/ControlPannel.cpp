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
/// \file   ControlPannel.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 27 septembre 2020, 20:04
///

#include "ControlPannel.h"
#include "utils/gui/view/Window.h"

ControlPannel::ControlPannel(int viewwidth, int viewheight, Window & window) :
  View(0,0,viewwidth, viewheight),
  _window(window),
  _background(SpriteSheet::loadFromFile(
      "medias/sprites/ui/background.png", 1, 1, window.renderer))
{
}

/// Draw the control pannel
void ControlPannel::draw() {
  SDL_Rect rect;
  rect.w = _viewWidth;
  rect.h = _viewHeight;
  rect.x = _offsetX;
  rect.y = _offsetY;
  _background->renderFrame(0, 0, _window.renderer, &rect);
}