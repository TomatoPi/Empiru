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
/// \file   EngineInterface.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 02:11
///

#ifndef ENGINEINTERFACE_H
#define ENGINEINTERFACE_H

#include <typeinfo>

#include "core/Pointer.h"
#include "core/Object.h"

class IGameAllocator {
public:
  
  virtual core::Pointer 
  createObject(const std::type_info&, const core::Object::Builder&) 
  noexcept = 0;
  
  virtual void discardObject(core::Pointer ptr) noexcept = 0;
};

#endif /* ENGINEINTERFACE_H */

