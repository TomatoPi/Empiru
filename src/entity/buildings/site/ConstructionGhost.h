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
/// \file   ConstructionGhost.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 5 octobre 2020, 21:35
///

#ifndef CONSTRUCTIONGHOST_H
#define CONSTRUCTIONGHOST_H

#include <typeinfo>
#include "utils/world/WorldObject.h"

class ConstructionGhost : public WorldObject {
private:
  
  const std::type_info* _type;
  bool                  _valid;
  
public:
    
  ConstructionGhost() : WorldObject(SHollow), _type(nullptr), _valid(false) {}
  
  const std::type_info& type() const noexcept {
    return *_type;
  }
  
  void valid(bool v) noexcept {
    _valid = v;
  }
  
  bool valid() const noexcept {
    return _valid;
  }
  
  
  struct Builder {
    const std::type_info& _type;
    const Position&       _position;
    Builder(const std::type_info& type, const Position& pos) noexcept :
      _type(type), _position(pos)
    {}
    
    void operator() (WorldPtr& ptr) const noexcept {
      ConstructionGhost& ghost(static_cast<ConstructionGhost&>(*ptr));
      ghost._type = &_type;
      ghost.pos(_position);
    }
  };
};

#endif /* CONSTRUCTIONGHOST_H */

