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

#ifndef HEX_VIEWPORT_H
#define HEX_VIEWPORT_H

#include "Axial.h"
#include "Consts.h"

namespace hex {

  /// \brief Utility object containing position, orientation and zoom of the camera
  class Viewport {
  public:

    static constexpr int HEXAGON_WIDTH  = 254; ///< Tile's on screen width
    static constexpr int HEXAGON_HEIGHT = 87;  ///< Tile's on screen height

    static const Axial VIEW_VX;  ///< Horizontal Axis
    static const Axial VIEW_VY;  ///< Vertical Axis

  private:

    int _tileWidth;   ///< Tile's width on viewport
    int _tileHeight;  ///< Tile's height on viewport

    Axial _viewport; ///< Viewport's diagonal vector
    Axial _pos;      ///< Camera's target (position at center of viewport)

    Axial _vx;  ///< Viewport's Horizontal vector
    Axial _vy;  ///< Viewport's Vertical vector

    Matrix _rotation;     ///< Camera's rotation matrix
    Matrix _antirotation; ///< Camera's rotation matrix's inverse

  public:

    /// \brief Constructor
    /// \param tileWidth  : Tile's width in pixel on viewport
    /// \param tileHeight : Tile's height in pixel on viewport 
    /// \param viewWidth  : View's width in pixel
    /// \param viewHeight : View's height in pixel
    Viewport(
      int tileWidth, int tileHeight, 
      int viewWidth, int viewHeight);

    /// \brief Convert a position on grid to a position on the screen
    void toPixel(const Axial & pos, int *x, int *y) const;
    /// \brief Convert a position on the screen to position in grid
    void fromPixel(int x, int y, Axial *pos) const;

    /// \brief return tile's width on viewport
    int tileHeight() const;
    /// \brief return tile's height on viewport
    int tileWidth() const;

    /// \brief Compute the position of viewport's upLeftCorner
    /// \param res : result in Axial coordinate system
    void upLeftCorner(Axial *res) const;

    /// \brief Return Viewport's x and y vectors in Axis cs
    /// Theses vectors can be used to move by one tile on viewport
    /// For every tile :
    ///   tile + x is the next tile by moving right on screen
    ///   tile + y is the next tile by moving down on screen
    void viewPortAxis(Axial *x, Axial *y) const;

    /// \brief return camera's targeted position
    const Axial & target() const;
    /// \brief set camera's targeted position
    void target(const Axial & pos);

    /// \brief return camera's rotation matrix
    const Matrix & rotation() const;
    /// \brief set camera's rotation matrix
    void rotation(const Matrix & m);
  };

}

#endif /* HEX_VIEWPORT_H */