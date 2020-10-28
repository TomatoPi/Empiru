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
/// \file   uid.h
/// \author tomato
///
/// \date 27 oct. 2020 22:28:46
///
#ifndef LIBS_UID_UID_H_
#define LIBS_UID_UID_H_

#include <unordered_set>
#include <chrono>

namespace uid {

class UIDGenerator {
public:
  using UID = std::size_t;
  UIDGenerator() noexcept = default;
  ~UIDGenerator() noexcept = default;
  const UID generateUID() noexcept {
    std::size_t val;
    do {
      val = reinterpret_cast<std::size_t>(&val)
          ^ std::chrono::system_clock::now().time_since_epoch().count();
    } while (_usedUIDs.emplace(val).second == false); // @suppress("Field cannot be resolved") // @suppress("Method cannot be resolved")
    return val;
  }
private:
  std::unordered_set<UID> _usedUIDs; // @suppress("Invalid template argument")
};

}

#endif /* LIBS_UID_UID_H_ */
