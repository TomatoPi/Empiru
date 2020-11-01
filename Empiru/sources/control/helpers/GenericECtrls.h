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
/// \file   GenericECtrls.h
/// \author tomato
///
/// \date 31 oct. 2020 21:30:16
///
#ifndef SOURCES_CONTROL_HELPERS_GENERICECTRLS_H_
#define SOURCES_CONTROL_HELPERS_GENERICECTRLS_H_

#include "../IEntityCtrl.h"

namespace ctrl {
namespace helpers {

class NullEntityController: public ctrl::IEntityCtrl {
public:
  NullEntityController() noexcept = default;
  virtual ~NullEntityController() noexcept = default;

  void leftClickOn(const game::EUID) noexcept override final;
  void leftClickOut(const game::EUID uid) noexcept override final;
  void RightClickOn(const game::EUID) noexcept override final;
  void RightClickOut(const game::EUID) noexcept override final;
  void cursorMoved() noexcept override final;
  void deselected(const game::EUID) noexcept override final;
};

class GenericEntityController: public ctrl::IEntityCtrl {
public:
  GenericEntityController() noexcept = default;
  virtual ~GenericEntityController() noexcept = default;

  void leftClickOn(const game::EUID) noexcept override final;
  void leftClickOut(const game::EUID uid) noexcept override final;
  void RightClickOn(const game::EUID) noexcept override final;
  void RightClickOut(const game::EUID) noexcept override final;
  void cursorMoved() noexcept override final;
  void deselected(const game::EUID) noexcept override final;
};

}  // namespace helpers
}  // namespace ctrl

#endif /* SOURCES_CONTROL_HELPERS_GENERICECTRLS_H_ */
