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
/// \file   PeonRenderer.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 16 septembre 2020, 12:48
///

#ifndef PEONRENDERER_H
#define PEONRENDERER_H

#include "gui/SmallObjectRenderer.h"

class PeonRenderer : public SmallObjectRenderer {
public:
  
  /// Constructor
  PeonRenderer(std::unique_ptr<SpriteSheet> s);
  
  /// \brief Draw a peon on screen, with (x,y) coordinate of bottom's middle
  virtual int renderAt(const WorldObject * obj, int ori, int x, int y, SDL_Renderer *rdr);
  
};

#endif /* PEONRENDERER_H */
