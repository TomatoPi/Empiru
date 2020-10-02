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
/// \file   ConstructSite.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 30 septembre 2020, 11:20
///

#ifndef CONSTRUCTSITE_H
#define CONSTRUCTSITE_H

#include "utils/world/WorldObject.h"

class ConstructionSite : public WorldObject {
public:
  ConstructionSite();
  ConstructionSite(const ConstructionSite &) = default;
  ConstructionSite & operator= (const ConstructionSite &) = default;
};

#endif /* CONSTRUCTSITE_H */
