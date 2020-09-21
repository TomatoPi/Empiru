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
/// \file   WorldRef.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 19 septembre 2020, 06:14
///

#ifndef WORLDREF_H
#define WORLDREF_H

#include "utils/world/WorldObject.h"

///
/// \brief Object used to keep safe references on WorldObjects
///
/// Because of object's blind storage, pointers and references may not be safe
///   due to data reordering.
/// This handler must answer this problem by insure proper tracking of 
///   referenced objects.
///
/// Thus, this handler must be used every time a singular object would be tracked
///
class WorldRef {
public:
  
  /// \brief Must return a reference to the associated object
  virtual WorldObject & operator-> () = 0;
  /// \brief Must return a reference to the associated object
  virtual const WorldObject & operator-> () const = 0;
  
  /// \brief Must return a reference to the associated object
  virtual WorldObject & operator* () = 0;
  /// \brief Must return a reference to the associated object
  virtual const WorldObject & operator* () const = 0;
  
protected:
  
  /// \brief Virtual destructor because of polymorphic object
  virtual ~WorldRef() = default;
};

#endif /* WORLDREF_H */
