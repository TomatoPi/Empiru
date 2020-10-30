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
/// \file   huid.h
/// \author tomato
///
/// \date 29 oct. 2020 16:05:57
///
#ifndef LIBS_UID_HUID_H_
#define LIBS_UID_HUID_H_

#include "uid.h"
#include <vector>

namespace uid {

class HierarchicalUID {
public:
  using HUID = std::size_t;

  class const_iterator {
  private:
    const HierarchicalUID *gen;
    HUID val;
  public:
    const_iterator(const HierarchicalUID *gen=nullptr, int val=0) noexcept :
        gen(gen), val(val) {
    }
    ~const_iterator() noexcept = default;
    const_iterator(const const_iterator&) noexcept = default;
    const_iterator& operator=(const const_iterator&) noexcept = default;

    const_iterator& operator++() noexcept {
      ++val;
      return *this;
    }
    const_iterator operator++(int) noexcept {
      const_iterator res(*this);
      ++val;
      return res;
    }
    const HUID& operator*() const noexcept {
      assert(gen);
      assert(val < gen->_fathers.size());
      return val;
    }
    const HUID& operator->() const noexcept {
      assert(gen);
      assert(val < gen->_fathers.size());
      return val;
    }
    friend bool operator==(const const_iterator&,
        const const_iterator&) noexcept;
    friend bool operator!=(const const_iterator&,
        const const_iterator&) noexcept;
  };

  /// \brief Construct an empty HUID generator
  HierarchicalUID() noexcept = default;
  ~HierarchicalUID() noexcept = default;
  /// \brief Create a new root KUID
  HUID newKind() noexcept {
    HUID uid(_fathers.size());
    _fathers.push_back(uid);
    return uid;
  }
  /// \brief Create a new KUID, derived from 'father'
  HUID newKind(HUID father) noexcept {
    HUID uid(_fathers.size());
    _fathers.push_back(father);
    return uid;
  }
  /// \brief Return true if 'kind' is derived from 'base'
  /// O(n) complexity, with n the depth of derivation tree
  bool isKindOf(HUID base, HUID kind) noexcept {
    if (base == kind)
      return true;
    while (_fathers[kind] != kind) {
      if (_fathers[kind] == base)
        return true;
      kind = _fathers[kind];
    }
    return false;
  }
  /// \brief Return list of types kind derives from
  const std::vector<HUID> basesOf(HUID kind) const noexcept {
    std::vector<HUID> res = { kind };
    while (_fathers[kind] != kind) {
      kind = _fathers[kind];
      res.emplace_back(kind);
    }
    return res;
  }

  const_iterator begin() const noexcept {
    return const_iterator(this);
  }
  const_iterator end() const noexcept {
    return const_iterator(this, _fathers.size());
  }

private:
  std::vector<HUID> _fathers;
};

}  // namespace uid

#endif /* LIBS_UID_HUID_H_ */
