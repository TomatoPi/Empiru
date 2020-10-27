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
/// \file   WorldInterface.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 16 septembre 2020, 10:47
///
#ifndef WORLDINTERFACE_H
#define WORLDINTERFACE_H

#include "Tile.h"

namespace world {

/// \brief Interface that must be used to comunicate with the World
class IMap {
public:

  /// \brief Prevent warning
  virtual ~IMap() noexcept = default;

  /// \brief Must return tile content at given pos, or null if empty
  virtual const Tile::Content* getContentAt(const world::Position&) const = 0;

  /// \brief Must return true if given pos is on the map
  virtual bool isOnMap(const world::Position&) const = 0;

  /// \brief Return true if given position is valid
  ///   if position is invalid, return false and return pointer to the obstacle
  ///   in 'obstacle' if relevant
  virtual bool tryPosition(const world::Position&, const Object::Pointer&,
      Object::Pointer*) const noexcept = 0;
};

} /* world */

#endif /* WORLDINTERFACE_H */

