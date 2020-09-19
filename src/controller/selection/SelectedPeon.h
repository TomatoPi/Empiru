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
/// \file   SelectedPeon.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 19 septembre 2020, 10:15
///

#ifndef SELECTEDPEON_H
#define SELECTEDPEON_H

#include "utils/engine/WorldRef.h"

/// \brief Utility object used to track a selected peon
struct SelectedPeon : public WorldObject {
  
  WorldRef *_peon; ///< The stalked peon
  
  SelectedPeon(); ///< Constructor
};

#endif /* SELECTEDPEON_H */
