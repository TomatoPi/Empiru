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
class GenericRenderer : public AbstractRenderer {  
protected:
  
  std::unique_ptr<SpriteSheet> _sheet;    ///< The sprite sheet
  std::unique_ptr<SpriteSheet> _mask;     ///< The mask sheet
  Blitter                      _blitter;  ///< The blitter
  int _offx;
  int _offy;
  
public:

  /// Constructor
  GenericRenderer(
      const char* sheet,
      const char* mask,
      SDL_Renderer* rdr,
      SDL_Renderer* mrdr,
      int offx=0, int offy=0, 
      Blitter b=Blitter())
  noexcept : 
    _sheet(SpriteAsset::loadFromFile(sheet, rdr)),
    _mask(SpriteAsset::loadFromFile(mask, mrdr)),
    _blitter(b),
    _offx(offx), _offy(offy)
  {  
  }
  GenericRenderer(
      const char* sheet,
      SDL_Renderer* rdr,
      int offx=0, int offy=0, 
      Blitter b=Blitter())
  noexcept : 
    _sheet(SpriteAsset::loadFromFile(sheet, rdr)),
    _mask(nullptr),
    _blitter(b),
    _offx(offx), _offy(offy)
  {  
  }
  
  /// \brief Draw the object at given position
  virtual void renderAt(
    const WorldRef * obj, 
    int ori, int x, int y,
    const hex::Viewport & view,
    SDL_Renderer *rdr)
  {
    SDL_Rect r;
    _blitter(&r, 
      _sheet->width(), _sheet->height(), 
      view.tileWidth(), view.tileHeight(), 
      x + _offx, y + _offy);
    _sheet->renderFrame(0, ori, rdr, &r);
  }
  
  /// \brief Render the object at given position, replacing the texture with
  ///   'color'
  virtual void renderAt(
    const WorldRef * obj,
    int ori, int x, int y,
    const hex::Viewport & view,
    SDL_Renderer * rdr,
    const SDL_Color & c)
  {
    SDL_Rect r;
    _blitter(&r, 
      _mask->width(), _mask->height(), 
      view.tileWidth(), view.tileHeight(), 
      x + _offx, y + _offy);
    _mask->setColorMod(c);
    _mask->renderFrame(0, ori, rdr, &r);
  }
  
  virtual void addTarget(const WorldRef * obj) noexcept {}
  virtual void removeTarget(const WorldRef * obj) noexcept {}
  virtual void targetSelected(const WorldRef * obj) noexcept {}
  virtual void targetDeselected(const WorldRef * obj) noexcept {}
  
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
