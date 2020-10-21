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
/// \brief Skeleton of Rendering objects
///

#ifndef GUI_RDR_ABSTRACTRENDERER_H
#define GUI_RDR_ABSTRACTRENDERER_H

#include "core/Pointer.h"
#include "utils/hex/Viewport.h"

#include <SDL2/SDL_render.h>

/// \brief Renderers are classes that know how to draw world objects
class ARenderer {
public:
  
  /// \brief Render the object at given position
  /// \param obj : the object beeing rendered
  /// \param ori : curent camera's orientation
  /// \param x   : object's x position on screen
  /// \param y   : object's y position on screen
  /// \param view: rendering viewport
  /// \param rdr : renderer
  /// \throw runtime_error on failure
  virtual void renderAt(
    const core::Pointer& obj, 
    int ori, int x, int y,
    const hex::Viewport & view) = 0;
  
  /// \brief Render the object at given position, replacing the texture with
  ///   'color'
  /// \param obj   : the object beeing drawn
  /// \param ori   : curent camera's orientation
  /// \param x     : object's x position on screen
  /// \param y     : object's y position on screen
  /// \param view  : rendering viewport
  /// \param rdr   : renderer
  /// \param color : color that must be used to draw
  /// \throw runtime_error on failure
  virtual void renderAt(
    const core::Pointer& obj,
    int ori, int x, int y,
    const hex::Viewport & view,
    const SDL_Color & color) = 0; 
};

#endif /* GUI_RDR_ABSTRACTRENDERER_H */
