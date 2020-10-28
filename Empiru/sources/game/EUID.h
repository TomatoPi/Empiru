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
#include <cstddef>

namespace game {

  /// \brief Entity UID
  using EUID = uid::UIDGenerator::UID;

} /* namespace Empiru */


#endif /* SOURCES_EMPIRU_EUID_H_ */
