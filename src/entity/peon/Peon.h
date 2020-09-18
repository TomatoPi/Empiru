/*
 * Copyright (C) 2020 Alexis
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
/// \file   Peon.h
/// \author Alexis CORREIA HENRIQUES <alex2ikangame@gmail.com>
///
/// \date 10 septembre 2020, 16:08
/// \brief The ultimate worker, useful to make anything you can think of
///

#ifndef PEON_H
#define PEON_H

#include <deque>
#include "utils/hex/HexCoords.h"
#include "utils/world/WorldObject.h"

/// \brief The ultimate worker, useful to make anything you can think of
/// \todo revise the path system
class Peon : public WorldObject {
private:

  /// \brief Store the list of targets positions, used as a stack
  typedef std::deque<FlatHexPosition> Path;

  Path            _path; ///< stack of in comming positions
  FlatHexPosition _dir;  ///< Peon's orientation

public:

  /// \brief Constructor
  Peon(const FlatHexPosition & pos);

  /// \brief Return current peon's target
  /// \pre peon has a target (path not empty)
  const FlatHexPosition & target() const;
  /// \brief Return current peon's orientation
  const FlatHexPosition & direction() const;

  bool hasPath() const;                       ///< true if path is not empty
  void clearPath();                           ///< remove all path's steps
  void addStep(const FlatHexPosition & pos);  ///< add pos on top of path
  void beginStep();                           ///< set dir according to top step
  void endstep();                             ///< remove top step
};

#endif /* PEON_H */