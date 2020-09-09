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
/// \file   HexCamera.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 8 septembre 2020, 03:59
/// \brief Implementation of an Isometric Camera for an Hexagonal map
///

#ifndef HEXCAMERA_H
#define HEXCAMERA_H

#include "utils/hex/HexCoords.h"

/// \brief Utility object containing position, orientation and zoom of the camera
class HexCamera {
public:
  
  static constexpr int HEXAGON_HEIGHT = 87;
  
private:
  
  int _tileWidth; ///< Tile's width on viewport
  int _tileHeight;///< Tile's height on viewport
  AxialPosition _pos; ///< Camera's target (position at center of viewport)
  
public:
  
  /// \brief Constructor
  /// \param tileWidth : Tile's width in pixels on viewport
  /// \param tileHeight : Tile's height in pixels on viewport 
  HexCamera(int tileWidth, int tileHeight);
  
  /// \brief Convert a position on grid to a position on the screen
  /// \param pos : position to convert
  /// \parma x : pixel column
  /// \param y : pixel row
  void toPixel(const GridPosition & pos, int *x, int *y) const;
  
  /// \brief return tile's width on viewport
  int tileHeight() const;
  /// \brief return tile's height on viewport
  int tileWidth() const;
  
  /// \brief return camera's targeted position
  const AxialPosition & target() const;
  /// \brief set camera's targeted position
  void target(const AxialPosition & pos);
  
  /// \brief Compute the position of viewport's upLeftCorner
  /// \param vWidth : viewport's width in pixels
  /// \param vHeight : viewpor's height in pixels
  void upLeftCorner(
    int vWidth, int vHeight, 
    OQOffsetPosition *p);
  
private:
  
  /// \see void toPixel(const GridPosition & pos, int *x, int *y) const
  void axialToPixel(const AxialPosition & pos, int *x, int *y) const;
  
  /// \brief Convert position on the screen to position on grid
  /// \parma x : pixel column
  /// \param y : pixel row
  /// \param pos : computed position
  void axialFromPixel(int x, int y, AxialPosition *pos) const;
};

#endif /* HEXCAMERA_H */