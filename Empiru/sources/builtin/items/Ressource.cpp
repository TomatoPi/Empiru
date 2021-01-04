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
/// \file   Ressource.cpp
/// \author tomato
///
/// \date 1 nov. 2020 00:59:45
///
#include "Ressources.h"
#include <items/Ressource.h>

namespace items {
namespace builtins {
namespace ressources {

const Ressource Wood = Ressource::RegisterRessource("wood",
    Ressource::Hierarchy().newKind());
const Ressource Rock = Ressource::RegisterRessource("rock",
    Ressource::Hierarchy().newKind());

}  // namespace ressources
}  // namespace builtins
}  // namespace items
