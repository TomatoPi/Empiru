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
/// \file   HexViewport.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 8 septembre 2020, 03:59
/// \brief Implementation of an Isometric Camera for an Hexagonal map
///

#ifndef HEXVIEWPORT_H
#define HEXVIEWPORT_H

#include "utils/hex/HexCoords.h"
#include "utils/math/Matrix.h"

/// \brief Utility object containing position, orientation and zoom of the camera
class HexViewport {
public:
  
  static constexpr int HEXAGON_WIDTH  = 254; ///< Tile's on screen width
  static constexpr int HEXAGON_HEIGHT = 87;  ///< Tile's on screen height
  
  static const Matrix22 ROTATE_LEFT; ///< Clockwise rotation
  static const Matrix22 ROTATE_RIGHT;///< Anti-Clockwise rotation
  static const FlatHexPosition VIEW_VX;  ///< Horizontal Axis
  static const FlatHexPosition VIEW_VY;  ///< Vertical Axis
  
private:
  
  int _tileWidth;   ///< Tile's width on viewport
  int _tileHeight;  ///< Tile's height on viewport
  
  FlatHexPosition _viewport; ///< Viewport's diagonal vector
  FlatHexPosition _pos;      ///< Camera's target (position at center of viewport)
  
  FlatHexPosition _vx;  ///< Viewport's Horizontal vector
  FlatHexPosition _vy;  ///< Viewport's Vertical vector
  
  Matrix22 _rotation;     ///< Camera's rotation matrix
  Matrix22 _antirotation; ///< Camera's rotation matrix's inverse
  
public:
  
  /// \brief Constructor
  /// \param tileWidth  : Tile's width in pixel on viewport
  /// \param tileHeight : Tile's height in pixel on viewport 
  /// \param viewWidth  : View's width in pixel
  /// \param viewHeight : View's height in pixel
  HexViewport(
    int tileWidth, int tileHeight, 
    int viewWidth, int viewHeight);
  
  /// \brief Convert a position on grid to a position on the screen
  void toPixel(const FlatHexPosition & pos, int *x, int *y) const;
  /// \brief Convert a position on the screen to position in grid
  void fromPixel(int x, int y, FlatHexPosition *pos) const;
  
  /// \brief return tile's width on viewport
  int tileHeight() const;
  /// \brief return tile's height on viewport
  int tileWidth() const;
  
  /// \brief Compute the position of viewport's upLeftCorner
  /// \param res : result in Axial coordinate system
  void upLeftCorner(FlatHexPosition *res) const;
  
  /// \brief Return Viewport's x and y vectors in Axis cs
  /// Theses vectors can be used to move by one tile on viewport
  /// For every tile :
  ///   tile + x is the next tile by moving right on screen
  ///   tile + y is the next tile by moving down on screen
  void viewPortAxis(FlatHexPosition *x, FlatHexPosition *y) const;
  /// \brief Screen horizontal axis in world's coordinate
  const FlatHexPosition & viewportVX() const;
  /// \brief Screen vertical axis in world's coordinate
  const FlatHexPosition & viewportVY() const;
  
  /// \brief return camera's targeted position
  const FlatHexPosition & target() const;
  /// \brief set camera's targeted position
  void target(const FlatHexPosition & pos);
  
  /// \brief return camera's rotation matrix
  const Matrix22 & rotation() const;
  /// \brief set camera's rotation matrix
  void rotation(const Matrix22 & m);
  
  /// \brief Return the x and y vectors, rotated by curent camera according to camera
  void rotatedAxialVectors(FlatHexPosition *ax, FlatHexPosition *ay) const;
};

#endif /* HEXVIEWPORT_H */