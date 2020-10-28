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
/// \file   Decorator.cpp
/// \author tomato
///
/// \date 28 oct. 2020 13:23:37
///
#include "Operator.h"
#include <cassert>

namespace game {

/// \brief Singleton
OKind& OKind::Get() noexcept {
  static OKind _instance;
  return _instance;
}
/// \brief Create a new root KUID
OUID OKind::newKind() noexcept {
  OUID uid(_fathers.size());
  _fathers.push_back(uid);
  return uid;
}
/// \brief Create a new KUID, derived from 'father'
OUID OKind::newKind(OUID father) noexcept {
  OUID uid(_fathers.size());
  _fathers.push_back(father);
  return uid;
}
/// \brief Return true if 'kind' is derived from 'base'
/// O(n) complexity, with n the depth of derivation tree
bool OKind::isKindOf(OUID base, OUID kind) noexcept {
  if (base == kind)
    return true;
  while (_fathers[kind] != kind) {
    if (_fathers[kind] == base)
      return true;
    kind = _fathers[kind];
  }
  return false;
}
std::vector<OUID> OKind::basesOf(OUID kind) noexcept {
  std::vector<OUID> res{kind};
  while (_fathers[kind] != kind) {
    kind = _fathers[kind];
    res.emplace_back(kind);
  }
  return res;
}

}  // namespace game
