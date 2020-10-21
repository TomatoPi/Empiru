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
/// \file   PeonBehaviour.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 18 septembre 2020, 19:18
///

#ifndef PEONBEHAVIOUR_H
#define PEONBEHAVIOUR_H

#include "entity/peon/PeonEntity.h"
#include "engine/core/entity/EntityBehaviour.h"

class PeonBehaviour : public EntityBeh {  
public:
  
  virtual void 
  operator() (Entity& peon, Pointer ptr) noexcept override;
};

#endif /* PEONBEHAVIOUR_H */
