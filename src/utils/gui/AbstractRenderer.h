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
/// \file   AbstractRenderer.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 14 septembre 2020, 12:49
///

#ifndef ABSTRACTRENDERER_H
#define ABSTRACTRENDERER_H

#include "utils/gui/SpriteSheet.h"
#include <SDL2/SDL_render.h>

class AbstractRenderer {
protected:
  
  std::unique_ptr<SpriteSheet> _sheet;
  
public:
  
  /// \brief Render the object at given position
  /// \param ori : curent camera's orientation
  /// \param x   : object's x position on screen
  /// \param y   : object's y position on screen
  /// \param rdr : renderer
  virtual int renderAt(int ori, int x, int y, SDL_Renderer *rdr) = 0;
  
protected:
  
  AbstractRenderer(std::unique_ptr<SpriteSheet> sheet);
};

#endif /* ABSTRACTRENDERER_H */
