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
/// \file   SelectedPeonRenderer.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 19 septembre 2020, 10:26
///

#ifndef SELECTEDPEONRENDERER_H
#define SELECTEDPEONRENDERER_H

#include "entity/peon/PeonRenderer.h"

class SelectedPeonRenderer : public PeonRenderer {
public:
  /// Constructor
  SelectedPeonRenderer(std::unique_ptr<SpriteSheet> s);
  
  /// \brief Draw the selection overlay on screen
  ///   with (x,y) coordinate of bottom's middle
  virtual int renderAt(
    const WorldRef * obj, 
    int ori, int x, int y,
    const hex::Viewport & view,
    SDL_Renderer *rdr);
  
  /// \brief Called when a new object associated with this renderer is created
  ///  may instanciate fine scope datas, like animation state
  virtual void addTarget(const WorldRef *obj);
  /// \brief Called when an object associated with this renderer is destroyed
  ///  may dealocate corresponding datas
  virtual void removeTarget(const WorldRef *obj);
};

#endif /* SELECTEDPEONRENDERER_H */
