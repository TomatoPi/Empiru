/*
 * Copyright (C) 2020 tomato
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
/// \file   Bridge.h
/// \author tomato
///
/// \date 27 oct. 2020 20:37:01
///
#ifndef SOURCES_GUI_BRIDGE_H_
#define SOURCES_GUI_BRIDGE_H_

#include <game/EUID.h>
#include "world/Position.h"
#include "Pixel.h"

namespace gui {

class Bridge {
public:
  virtual ~Bridge() noexcept = default;
  virtual std::pair<world::Position, game::EUID> at(const Pixel&) noexcept = 0;
  virtual world::Position fromPixel(const Pixel&) noexcept = 0;
};

}  // namespace gui

#endif /* SOURCES_GUI_BRIDGE_H_ */