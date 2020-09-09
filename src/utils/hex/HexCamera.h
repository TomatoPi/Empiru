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
  
  static constexpr int HEXAGON_WIDTH  = 256;
  static constexpr int HEXAGON_HEIGHT = 87;
  
private:
  
  int _tileWidth;   ///< Tile's width on viewport
  int _tileHeight;  ///< Tile's height on viewport
  FlatHexPosition _viewport; /// Viewport's diagonal vector
  FlatHexPosition _pos;      ///< Camera's target (position at center of viewport)
  
public:
  
  /// \brief Constructor
  /// \param tileWidth  : Tile's width in pixel on viewport
  /// \param tileHeight : Tile's height in pixel on viewport 
  /// \param viewWidth  : View's width in pixel
  /// \param viewHeight : View's height in pixel 
  HexCamera(
    int tileWidth, int tileHeight, 
    int viewWidth, int viewHeight);
  
  /// \brief Convert a position on grid to a position on the screen
  /// \param pos : position to convert
  /// \parma x : pixel column
  /// \param y : pixel row
  void toPixel(const FlatHexPosition & pos, int *x, int *y) const;
  /// \brief Convert a position on grid to position of it center on the screen
  /// \param pos : position to convert
  /// \parma x : pixel column
  /// \param y : pixel row
  void tileCenter(const FlatHexPosition & pos, int *x, int *y) const;
  
  /// \brief return tile's width on viewport
  int tileHeight() const;
  /// \brief return tile's height on viewport
  int tileWidth() const;
  
  /// \brief return camera's targeted position
  const FlatHexPosition & target() const;
  /// \brief set camera's targeted position
  void target(const FlatHexPosition & pos);
  
  /// \brief Compute the position of viewport's upLeftCorner
  /// \param res : result in Axial coordinate system
  void upLeftCorner(FlatHexPosition *res);
  /// \brief Return Viewport's x and y vectors in Axis cs
  /// Theses vectors can be used to move by one tile on viewport
  /// For every tile :
  ///   tile + x is the next tile by moving right on screen
  ///   tile + y is the next tile by moving down on screen
  void viewPortAxis(FlatHexPosition *x, FlatHexPosition *y);
};

#endif /* HEXCAMERA_H */