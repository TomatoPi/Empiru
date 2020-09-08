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
/// \file   HexCamera.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 8 septembre 2020, 03:59
///

#include <cassert>

#include "HexCamera.h"
#include "utils/log.h"

HexCamera::HexCamera(int tileWidth, float heightFactor) :
  _tw(tileWidth),
  _hf(heightFactor)
{
  assert(0 < tileWidth);
  assert(0 < heightFactor);
}

void HexCamera::toPixel(const GridPosition & pos, int *x, int *y) const {
  assert(x);
  assert(y);
  *x = 4 * (pos._w + 2) * tileWidth();
  *y = 2 * (pos._h + 1) * tileHeight();
}

float HexCamera::tileHeight() const {
  return _tw * whfactor * _hf;
}
float HexCamera::tileWidth() const {
  return _tw;
}