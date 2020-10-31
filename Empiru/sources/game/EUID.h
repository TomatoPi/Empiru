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
/// \file   Types.h
/// \author tomato
///
/// \date 27 oct. 2020 20:46:42
///
#ifndef SOURCES_EMPIRU_EUID_H_
#define SOURCES_EMPIRU_EUID_H_

#include <uid/uid.h>
#include <uid/huid.h>
#include <ostream>

namespace game {

/// \brief Entity UID
class EUID {
public:
  using IDGen = uid::UIDGenerator<std::uint64_t, ((~static_cast<std::uint64_t>(0)) >> 16)>;
  using UID = IDGen::UID;
  using HierarchyGen = uid::HierarchicalUID<std::uint16_t>;
  using Kind = HierarchyGen::HUID;
private:
  std::uint64_t val;
public:
  const Kind kind() const noexcept {
    return val >> 48;
  }
  const UID uid() const noexcept {
    return val & ((~0) >> 16);
  }
  EUID() noexcept : EUID(InvalidKind(), 0) {
  }
  EUID(Kind k, UID u) noexcept :
      val(
          (static_cast<std::uint64_t>(k) << 48)
              | (u & (~static_cast<std::uint64_t>(0)) >> 16)) {
  }

  EUID(const EUID&) noexcept = default;
  EUID& operator= (const EUID&) noexcept = default;
  ~EUID() noexcept = default;

  static HierarchyGen& Hierarchy() noexcept {
    static HierarchyGen _hierarchy;
    return _hierarchy;
  }
  static Kind InvalidKind() noexcept {
    return Hierarchy().newKind();
  }
  explicit operator bool() const noexcept {
    return val != 0;
  }
  friend std::ostream& operator<<(std::ostream &s, const EUID &a) noexcept;
  friend bool operator<(const EUID &a, const EUID &b) noexcept;
  friend bool operator==(const EUID &a, const EUID &b) noexcept;
  friend struct std::hash<EUID>;
};

} /* namespace Empiru */

template<>
struct std::hash<game::EUID> {
  std::size_t operator()(const game::EUID &a) const noexcept {
    return a.val;
  }
};

#endif /* SOURCES_EMPIRU_EUID_H_ */
