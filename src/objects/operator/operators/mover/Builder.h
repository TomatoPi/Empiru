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
/// \file   Builder.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 24 octobre 2020, 12:15
///

#ifndef OPERATOR_MOVER_BUILDER_H
#define OPERATOR_MOVER_BUILDER_H

#include "objects/operator/core/Operator.h"
#include "world/core/IWorldMap.h"

namespace operators {
  
  class MoverBuilder : public Operator::Builder {
  private:

    IWorldMap*      _worldMap;
    core::Pointer   _object;
    float           _speed;

  public :

    MoverBuilder(
      IWorldMap* worldMap,
      const core::Pointer& object, 
      float speed) noexcept;

    void operator() (core::Pointer& ptr) noexcept override;
  };
}

#endif /* OPERATOR_MOVER_BUILDER_H */

