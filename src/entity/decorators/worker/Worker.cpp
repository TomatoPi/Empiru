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

#include "Worker.h"
#include "entity/decorators/deposit/Deposit.h"

namespace decorator { 

  /// \brief Change the collect site of this collector
  void Worker::setWorkSite(const Pointer& ptr) noexcept {
    _worksite = ptr;
    updateStatus();
    workChanged();
  }
  Pointer Worker::worksite() const noexcept {
    return _worksite;
  }

  /// \brief Return the collector's status
  Worker::Status Worker::status() const noexcept {
    return _status;
  }
  /// \brief Update collector's status
  Worker::Status Worker::updateStatus() noexcept {
    if (!_worksite) {
      if (_worksite.isDeprecated()) {
        return _status = Status::CannotWork;
      } else {
        return _status = Status::Idle;
      }
    }
    else {
      const Entity& entity = *_worksite->entity();
      if (entity.obj().radius() + _entity->obj().radius() + 0.1
        < WorldObject::Position::distance(
            entity.obj().pos(), _entity->obj().pos()))
      {
        return _status = Status::TooFar;
      }
      else if (isWorkDone()) {
        return _status = Status::WorkDone;
      } 
      else {
        return _status = Status::Working;
      }
    }
  }

  /// \brief Compute one collect tick
  void Worker::work() noexcept {
    if (_status == Status::Working) {
      doWork();
    }
  }
}