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
/// \file   Harvestable.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 21 septembre 2020, 18:23
///

#ifndef HARVESTABLE_H
#define HARVESTABLE_H

#include "Stack.h"

/// \brief Component for WorldObjects that are ressources deposits
/// \todo this class is very ugly, make it clean
class Harvestable : public Stack {
public:
  Harvestable(Stack::Ressource type, int size) noexcept : 
    Stack(type, size)
  {    
  }
  virtual ~Harvestable() = default;
};

#endif /* HARVESTABLE_H */
