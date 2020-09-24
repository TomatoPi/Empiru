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
/// \file   SelectedPeonBehaviour.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 19 septembre 2020, 10:22
///

#ifndef SELECTEDPEONBEHAVIOUR_H
#define SELECTEDPEONBEHAVIOUR_H

#include "utils/engine/Behaviourer.h"

/// \brief Behaviour of the utility object 'SelectedPeon'
/// update it's position according to peon's one
class SelectedPeonBehav : public Behaviourer {
public:
  /// \brief Must compute one behaviour tick of obj
  virtual void tick(WorldObject & obj, WorldRef *ref, WorldInterface & world);
};

#endif /* SELECTEDPEONBEHAVIOUR_H */
