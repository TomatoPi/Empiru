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
/// \file   Ressource.h
/// \author tomato
///
/// \date 29 oct. 2020 17:42:08
///
#ifndef SOURCES_BUILTIN_ITEMS_RESSOURCE_H_
#define SOURCES_BUILTIN_ITEMS_RESSOURCE_H_

#include <uid/huid.h>

namespace items {

class Ressource {
public:
  using Kind = uid::HierarchicalUID::HUID;
private:
  Kind _kind;
public:
  Ressource(const Kind k = InvalidKind()) noexcept :
      _kind(k) {
  }
  ~Ressource() noexcept = default;
  Ressource(const Ressource&) noexcept = default;
  Ressource& operator= (const Ressource&) noexcept = default;

  const Kind kind() const noexcept {
    return _kind;
  }

  static uid::HierarchicalUID& Hierarchy() noexcept {
    static uid::HierarchicalUID _instance;
    return _instance;
  }

  static const Kind& InvalidKind() noexcept {
    static Kind _invalid(Hierarchy().newKind());
    return _invalid;
  }
  static const Ressource& Invalid() noexcept {
    static Ressource _invalid(InvalidKind());
    return _invalid;
  }

  friend bool operator<(const Ressource &a, const Ressource &b) noexcept;
  friend bool operator==(const Ressource &a, const Ressource &b) noexcept;
  friend struct std::hash<Ressource>;
};

}  // namespace items

template <>
struct std::hash<items::Ressource> {
  std::size_t operator()(const items::Ressource &a) const noexcept {
    return a._kind;
  }
};

#endif /* SOURCES_BUILTIN_ITEMS_RESSOURCE_H_ */
