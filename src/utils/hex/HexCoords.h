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
/// \file   HexCoords.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 8 septembre 2020, 02:38
/// \brief File containing utilities for Hexagonal Grids
///
/// \see https://www.redblobgames.com/grids/hexagons/
///

#ifndef HEXCOORDS_H
#define HEXCOORDS_H

/// \brief Position in Odd-q Offset System
struct OQOffsetPosition {
  int _lig; ///< Tile's line
  int _col; ///< Tile's column
};

/// \brief Position in Cartesian Coordinate System 
///   with origin on Tile's (0,0) center
/// Coordinates are relatives to tile's dimension, width flat disposition
struct GridPosition {
  float _w; ///< Horizontal position in quarter of tile's width
  float _h; ///< Vertical position in half of tile's height
};

/// \brief Convert an Odd-q OffsetPosition to a GridPosition
void convertPosition(
  const OQOffsetPosition & src, 
  GridPosition * dest);

#endif /* HEXCOORDS_H */
