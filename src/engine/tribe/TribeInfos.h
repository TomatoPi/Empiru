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

#include <array>
#include <unordered_set>
#include "ressources/core/Stack.h"
#include "utils/pattern/BigObserver.h"
#include "utils/misc/Counter.h"
#include "engine/core/decorator/Pointer.h"

class TribeInfos : public BigObserver {
public:
  
  typedef std::array<int,Stack::RessourceCount> TribeStocks;
  
private:
  
  typedef std::unordered_set<decorator::Pointer,alloc::PtrHash,alloc::PtrEquals>
  ObjectsList;
  
  ObjectsList _objects;
  TribeStocks _stocks;
  Counter     _cptr;
  
public:
  
  TribeInfos() noexcept;
  TribeInfos(const TribeInfos &) noexcept = default;
  TribeInfos & operator= (const TribeInfos &) noexcept = default;
  
  void update() noexcept;
  
  const TribeStocks & stocks() const noexcept {
    return _stocks;
  }
  
private:
  
  void init() noexcept {
    _stocks.fill(0);
  }
  
  void addStack(const Stack & stack) noexcept {
    _stocks[static_cast<std::size_t>(stack.type())] += stack.size();
  }
};

#endif /* TRIBEINFOS_H */
