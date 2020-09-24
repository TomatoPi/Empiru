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
/// \file   Tree.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 17 septembre 2020, 08:45
/// \brief Tree WorldObject declaration
///

#ifndef TREE_H
#define TREE_H

#include "utils/world/WorldObject.h"
#include "utils/world/Harvestable.h"

/// \brief Trees are beautiful things which don't do special things at this moment
class Tree : public WorldObject, public Harvestable {
  
public:
  
  /// \brief Constructor
  Tree();
};

#endif /* TREE_H */
