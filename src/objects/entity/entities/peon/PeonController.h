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
/// \file   PeonController.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 07:46
///

#ifndef PEONCONTROLLER_H
#define PEONCONTROLLER_H

#include "controller/core/IEntityController.h"
#include "controller/core/IGameController.h"
#include "world/core/IWorldMap.h"
#include "core/IGameAllocator.h"

namespace peon {
  class PeonController : public IEntityController {
  private:

    IGameController& _controller;
    IGameAllocator&  _allocator;
    IWorldMap&       _worldmap;

  public:

    PeonController(
      IGameController& controller, 
      IGameAllocator& alloc,
      IWorldMap& map) 
    noexcept :
      _controller(controller), _allocator(alloc), _worldmap(map)
    {
    }

    virtual void leftClickOn(core::Pointer ptr) noexcept override;
    virtual void leftClickOut(core::Pointer ptr) noexcept override;
    virtual void RightClickOn(core::Pointer ptr) noexcept override;
    virtual void RightClickOut(core::Pointer ptr) noexcept override;
    virtual void cursorMoved() noexcept override;
    virtual void deselected(core::Pointer ptr) noexcept override;
  };
}

#endif /* PEONCONTROLLER_H */
