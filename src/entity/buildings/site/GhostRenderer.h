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
/// \file   GhostRenderer.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 5 octobre 2020, 23:52
///

#ifndef GHOSTRENDERER_H
#define GHOSTRENDERER_H

#include "utils/gui/renderer/AbstractRenderer.h"
#include "gui/GenericRenderer.h"

/// \brief Renderers are classes that know how to draw world objects
class GhostRenderer : public AbstractRenderer {
private:
  
  typedef std::unordered_map<WorldPtr,bool,WorldPtrHash,WorldPtrEquals> 
    Targets;
  
  Targets       _targets;
  OnTileBlitter _blitter;
  
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
    const WorldPtr& obj, 
    int ori, int x, int y,
    const hex::Viewport & view);
  
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
    const WorldPtr& obj,
    int ori, int x, int y,
    const hex::Viewport & view,
    const SDL_Color & color) 
  noexcept {}
  
  /// \brief Called when a new object associated with this renderer is created
  ///  may instanciate fine scope datas, like animation state
  virtual void addTarget(const WorldPtr& obj) noexcept;
  /// \brief Called when an object associated with this renderer is destroyed
  ///  may dealocate corresponding datas
  virtual void removeTarget(const WorldPtr& obj) noexcept;
  /// \brief Called when an object associated with this renderer is selected
  ///  may remember draw a special overlay around it
  virtual void targetSelected(const WorldPtr& obj) noexcept {}
  /// \brief Called when an object associated with this renderer is deselected
  ///  may remember to stop draw special overlay
  virtual void targetDeselected(const WorldPtr& obj) noexcept {}
};

#endif /* GHOSTRENDERER_H */
