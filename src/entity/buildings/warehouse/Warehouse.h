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
/// \file   Warehouse.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 7 octobre 2020, 00:56
///

#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "utils/world/WorldObject.h"
#include "utils/world/Storage.h"

class Warehouse : public WorldObject, public Storage {
public:
  Warehouse();
  Warehouse(const Warehouse &) = default;
  Warehouse& operator= (const Warehouse&) = default;
};

#endif /* WAREHOUSE_H */
