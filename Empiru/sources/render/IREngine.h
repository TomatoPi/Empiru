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
/// \file   IREngine.h
/// \author tomato
///
/// \date 28 oct. 2020 15:20:39
///
#ifndef SOURCES_RENDER_IRENGINE_H_
#define SOURCES_RENDER_IRENGINE_H_

#include <game/EUID.h>
#include "ATarget.h"

namespace render {
class IREngine {
private:
  static IREngine *_instance;
public:

  static void registerREngine(IREngine* m) noexcept {
    _instance = m;
  }

  static IREngine& Get() noexcept {
    return *_instance;
  }

  virtual ~IREngine() noexcept = default;
  virtual ATarget& getTarget(const game::EUID) noexcept = 0;
};
}

#endif /* SOURCES_RENDER_IRENGINE_H_ */
