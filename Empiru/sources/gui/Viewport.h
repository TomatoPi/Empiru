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

#include "Pixel.h"

#include <hex/Axial.h>
#include <hex/Consts.h>
#include <SDL2/SDL_rect.h>
#include <observer/SuperObserver.h>
#include <world/Position.h>

namespace gui {

namespace Events {

struct ViewportMoved {
};
struct ViewportRotated {
};

}  // namespace Events

/// \brief Utility object containing position, orientation and zoom of the camera
class Viewport: public SuperObserver::Subject<Viewport, Events::ViewportMoved,
    Events::ViewportRotated> {
public:

  template<typename E>
  using Subject = SuperObserver::Subject<Viewport, E>; // @suppress("Invalid template argument")

  static constexpr int HEXAGON_WIDTH = 254; ///< Tile's on screen width
  static constexpr int HEXAGON_HEIGHT = 87; ///< Tile's on screen height

  static const hex::Axial VIEW_VX; ///< Horizontal Axis
  static const hex::Axial VIEW_VY; ///< Vertical Axis

private:

  int _tileWidth;  ///< Tile's width on viewport
  int _tileHeight; ///< Tile's height on viewport
  int _offsetX;
  int _offsetY;
  int _viewWidth;
  int _viewHeight;

  hex::Axial _viewport; ///< Viewport's diagonal vector
  hex::Axial _pos; ///< Camera's target (position at center of viewport)

  hex::Axial _vx; ///< Viewport's Horizontal vector
  hex::Axial _vy; ///< Viewport's Vertical vector

  hex::Matrix _rotation; ///< Camera's rotation matrix
  hex::Matrix _antirotation; ///< Camera's rotation matrix's inverse

public:

  /// \brief Constructor
  /// \param offsetX    : View's up left corner X
  /// \param offsetY    : View's up left corner Y
  /// \param tileWidth  : Tile's width in pixel on viewport
  /// \param tileHeight : Tile's height in pixel on viewport
  /// \param viewWidth  : View's width in pixel
  /// \param viewHeight : View's height in pixel
  Viewport(int offsetX, int offsetY, int tileWidth, int tileHeight,
      int viewWidth, int viewHeight) noexcept;

  /// \brief Convert a position on grid to a position on the screen
  Pixel toPixel(const hex::Axial &pos) const noexcept;
  /// \brief Convert a position on the screen to position in grid
  hex::Axial fromPixel(const Pixel &pix) const noexcept;

  /// \brief return tile's width on viewport
  int tileHeight() const noexcept;
  /// \brief return tile's height on viewport
  int tileWidth() const noexcept;
  Pixel tileSize() const noexcept;
  int viewHeight() const noexcept;
  int viewWidth() const noexcept;

  bool isInView(const Pixel& pix) const noexcept;
  bool doesIntersect(const SDL_Rect& r) const noexcept;

  /// \brief Compute the position of viewport's upLeftCorner
  /// \param res : result in Axial coordinate system
  hex::Axial upLeftCorner() const noexcept;

  /// \brief Return Viewport's x and y vectors in Axis cs
  /// Theses vectors can be used to move by one tile on viewport
  /// For every tile :
  ///   tile + x is the next tile by moving right on screen
  ///   tile + y is the next tile by moving down on screen
  struct ViewAxices {
    hex::Axial vx;
    hex::Axial vy;
  };
  ViewAxices viewPortAxis() const noexcept;

  /// \brief return camera's targeted position
  const hex::Axial& target() const noexcept;
  /// \brief set camera's targeted position
  void target(const hex::Axial &pos) noexcept;

  /// \brief return camera's rotation matrix
  const hex::Matrix& rotation() const noexcept;
  /// \brief set camera's rotation matrix
  void rotation(const hex::Matrix &m) noexcept;
};

} /* namespace gui */

#endif /* HEX_VIEWPORT_H */
