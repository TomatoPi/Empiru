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
/// \file   GenericRenderer.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 11 septembre 2020, 02:27
/// \brief provide template for basic and generic renderers
///

#ifndef GENERICRENDERER_H
#define GENERICRENDERER_H

#include <memory>
#include "core/Pointer.h"
#include "gui/core/AbstractRenderer.h"
#include "utils/assets/SpriteSheet.h"
#include "utils/assets/GraphicAssetsRegister.h"

/// \brief Generic renderer parameterized by the functor used to compute
///   blit coordinates
/// This functor must have the following prototype :
///
/// void (SDL_Rect * r, int w, int h, int tw, int th, int x, int y)
///
/// with :
///
///   rect : return computed blit rectangle
///
///   w    : blit width
///   h    : blit height
///
///   tw   : tile's width on screen
///   th   : tile's height on screen
///   x    : tile's center x
///   y    : tile's center y
///
template <typename Blitter>
class GenericRenderer : public ARenderer {  
protected:
  
  std::shared_ptr<SpriteSheet> _sheet;    ///< The sprite sheet
  std::shared_ptr<SpriteSheet> _mask;     ///< The mask sheet
  std::shared_ptr<SpriteSheet> _select;   ///< The slection sheet
  Blitter                      _blitter;  ///< The blitter
  int _offx;
  int _offy;
  
public:

  /// Constructor
  GenericRenderer(
      const gui::ObjectAsset& assets,
      int offx=0, int offy=0, 
      Blitter b=Blitter())
  noexcept : 
    _sheet(assets._sheet),
    _mask(assets._mask),
    _select(assets._select),
    _blitter(b),
    _offx(offx), _offy(offy)
  {  
  }
  
  /// \brief Draw the object at given position
  virtual void renderAt(
    const core::Pointer& obj, 
    int ori, int x, int y,
    const hex::Viewport & view)
  override {
    SDL_Rect r;
    _blitter(&r, 
      _sheet->width(), _sheet->height(), 
      view.tileWidth(), view.tileHeight(), 
      x + _offx, y + _offy);
    _sheet->renderFrame(0, ori, &r);
  }
  
  /// \brief Render the object at given position, replacing the texture with
  ///   'color'
  virtual void renderAt(
    const core::Pointer& obj,
    int ori, int x, int y,
    const hex::Viewport & view,
    const SDL_Color & c)
  override {
    SDL_Rect r;
    _blitter(&r, 
      _mask->width(), _mask->height(), 
      view.tileWidth(), view.tileHeight(), 
      x + _offx, y + _offy);
    _mask->setColorMod(c);
    _mask->renderFrame(0, ori, &r);
  }
};

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
class OnTileBlitter {
public:
  void operator() (SDL_Rect * rect,
      int w, int h, int tw, int th, int x, int y) const noexcept 
  {
    rect->w = w, rect->h = h;
    rect->x = x - rect->w/2;
    rect->y = y + th/2 - rect->h;
  }
};

/// \brief Put the rectangle 'r' as if (x,y) was object foot's position
/// \see void blitTile(SDL_Rect * r, int w, int h, int tw, int th, int x, int y)
class OnFootBlitter {
public:
  void operator() (SDL_Rect * rect,
      int w, int h, int tw, int th, int x, int y) const noexcept 
  {
    rect->w = w, rect->h = h;
    rect->x = x - rect->w/2;
    rect->y = y - rect->h;
  }
};


#endif /* GENERICRENDERER_H */
