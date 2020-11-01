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
/// \file   TribeInfos.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 29 septembre 2020, 00:22
///
#ifndef TRIBEINFOS_H
#define TRIBEINFOS_H

#include <items/Stack.h>
#include <items/StackHelpers.h>
#include <set>

namespace tribe {

class TribeInfos {
public:

  using TribeStocks = std::set<items::Stack, items::helpers::StackTypeLess>;

private:

  TribeStocks _stocks;

public:

  TribeInfos() noexcept;

  const TribeStocks& stocks() const noexcept {
    return _stocks;
  }

private:
  items::Stack getOrAdd(items::Ressource type) noexcept;
  void grow(items::Ressource type, int qty) noexcept;
};

}  // namespace tribe

#endif /* TRIBEINFOS_H */
