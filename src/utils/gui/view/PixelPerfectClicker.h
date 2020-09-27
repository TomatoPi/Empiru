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
/// \file   PixelPerfectClicker.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 27 septembre 2020, 11:13
///

#ifndef PIXELPERFECTCLICKER_H
#define PIXELPERFECTCLICKER_H

#include "utils/world/WorldRef.h"

class PixelPerfectClicker {
public:
  virtual ~PixelPerfectClicker() noexcept = default;
  
  virtual void updateClickZones() = 0;
  
  virtual WorldRef * objectAt(int x, int y) const noexcept = 0;
};

#endif /* PIXELPERFECTCLICKER_H */
