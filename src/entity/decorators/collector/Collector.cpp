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
/// \file   Collector.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 octobre 2020, 22:18
///

#include "Collector.h"

void CollectorDecorator::setCollectSite(const DecoratorPtr& ptr) noexcept {
  _collectSite = ptr;
  updateStatus();
}
void CollectorDecorator::setStorageSite(const DecoratorPtr& ptr) noexcept {
  _storageSite = ptr;
  updateStatus();
}

DecoratorPtr CollectorDecorator::target() const noexcept {
  switch (_action) {
  case Action::None        : 
    return DecoratorPtr(nullptr);
  case Action::FillStorage :
    if (_status == )
  }
}
  
void CollectorDecorator::giveAction(Action action) noexcept {
  
}
void CollectorDecorator::updateStatus() noexcept {
  
}

void CollectorDecorator::tick() noexcept {
  
}