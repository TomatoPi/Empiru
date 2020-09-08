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

/// \TODO Le calcul de la hauteur d'affichage d'un tuile est superflu
///   et pas très malin, il suffit de décider manuellement du nombre
///   de pixels de haut et d'ensuite calculer (si besoin ??) l'angle
///   de la caméra, de sorte à avoir des valeurs rondes pour les
///   alignements
  
  static constexpr float whfactor = 0.866025404;  ///< height / width
  static constexpr float vfactor = 0.387124249;   ///< Magic
  
private:
  
  float _tw; ///< Tile's width in pixel
  float _hf; ///< Vertical size ratio
  
public:
  
  /// \brief Constructor
  /// \param tileWidth : Tile's width in pixels on the viewport
  /// \param heightFactor : ratio between object's height on map and on viewport 
  HexCamera(int tileWidth, float heightFactor);
  
  /// \brief Convert a position on grid to a position on the screen
  /// \param pos : position to convert
  /// \parma x : position's abscissa
  /// \param y : position's ordinate
  void toPixel(const GridPosition & pos, int *x, int *y) const;
  
  /// \brief return tile's width on viewport
  float tileHeight() const;
  /// \brief return tile's height on viewport
  float tileWidth() const;
};

#endif /* HEXCAMERA_H */