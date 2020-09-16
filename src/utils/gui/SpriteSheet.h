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
/// \file   Sprite.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 8 septembre 2020, 04:28
/// \brief Provide basic object to load and draw sprites
///

#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <memory>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

/// \brief Provide basic object to load and draw sprites
class SpriteSheet {
protected:
  
  SDL_Texture *_sheet; ///< The sheet
  int _w; ///< Sprite's width
  int _h; ///< Sprite's height
  unsigned int _rows; ///< Number of frames by column
  unsigned int _cols; ///< Number of frames by row
  
public:
  
  /// \brief Constructor
  SpriteSheet(SDL_Texture *t, 
          int w, int h,
          unsigned int rows, 
          unsigned int cols);
  
  /// \brief Destructor
  ~SpriteSheet();
  
  /// \brief Loads a sprite from an image file
  /// \param path : file's path
  /// \param rows : number of frames by row
  /// \param cols : number of frames by column
  /// \param rdr  : SDL_Renderer associated with targeted viewport
  /// \return NULL on failure
  static std::unique_ptr<SpriteSheet> loadFromFile(
    const char *path, 
    unsigned int rows, 
    unsigned int cols, 
    SDL_Renderer *rdr);
  
  /// \brief Render the sprite in given SDL_Rect
  int renderFrame(
    unsigned int row,
    unsigned int col,
    SDL_Renderer *renderer,
    const SDL_Rect *dest);
  
  /// \brief return sprite's width
  int width() const;
  /// \brief return sprite's height
  int height() const;
  
  /// \brief return number of frames by row on the sheet
  unsigned int colCount() const;
  /// \brief return number of frames by column on the sheet
  unsigned int rowCount() const;
  
  /// \brief change number of frames by rows and columns on the sheet
  int recut(unsigned int rows, unsigned int cols);
};

#endif /* SPRITE_H */
