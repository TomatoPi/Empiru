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
/// \date 11 septembre 2020, 02:27
///

#ifndef GENERICRENDERER_H
#define GENERICRENDERER_H

#include <memory>
#include "utils/gui/renderer/AbstractRenderer.h"
#include "utils/gui/assets/SpriteSheet.h"

/// \brief Generic renderer parameterized by the functor used to compute
///   blit coordinates
/// This functor must have the following prototype :
///
/// void (SDL_Rect * r, int w, int h, int tw, int th, int x, int y)
///
/// with :
///
///   r  : return computed blit rectangle
///
///   w  : blit width
///   h  : blit height
///
///   tw : tile's width on screen
///   th : tile's height on screen
///   x  : tile's center x
///   y  : tile's center y
///
template <typename Blitter>
class GenericRenderer : public AbstractRenderer {  
protected:
  
  std::unique_ptr<SpriteSheet> _sheet;
  Blitter                      _blitter;
  
public:

  /// Constructor
  GenericRenderer(
      std::unique_ptr<SpriteSheet> s, 
      Blitter b=Blitter()) : 
    _sheet(std::move(s)),
    _blitter(b)
  {  
  }
  
  /// \brief Draw the object at given position
  virtual int renderAt(
    const WorldObject * obj, 
    int ori, int x, int y,
    const HexViewport & view,
    SDL_Renderer *rdr) 
  {
    SDL_Rect r;
    _blitter(&r, 
      _sheet->width(), _sheet->height(), 
      view.tileWidth(), view.tileHeight(), 
      x, y);
    return _sheet->renderFrame(0, ori, rdr, &r);
  }
  
  virtual void addTarget(const WorldObject *obj) {}
  virtual void removeTarget(const WorldObject *obj) {}
  
};

#endif /* GENERICRENDERER_H */
