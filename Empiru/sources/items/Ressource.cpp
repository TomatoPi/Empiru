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
/// \file   Ressource.cpp
/// \author tomato
///
/// \date 29 oct. 2020 23:50:06
///
#include "Ressource.h"
#include <unordered_map>
#include <cassert>

namespace {
  static std::unordered_map<std::string,items::Ressource> _register;
}

namespace items {

bool operator<(const Ressource &a, const Ressource &b) noexcept {
  return a._kind < b._kind;
}
bool operator==(const Ressource &a, const Ressource &b) noexcept {
  return a._kind == b._kind;
}

Ressource Ressource::RegisterRessource(const std::string& name, Kind kind) noexcept {
  auto [itr, result] = _register.emplace(name, Ressource(kind, name));
  assert(result);
  return itr->second;
}
Ressource Ressource::Get(const std::string& name) noexcept {
  return _register.at(name);
}

}  // namespace items
