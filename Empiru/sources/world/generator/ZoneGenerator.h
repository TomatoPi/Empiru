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

/* 
 * File:   ZoneGenerator.h
 * Author: Alexis
 *
 * Created on 20 septembre 2020, 17:00
 */

#ifndef ZONEGENERATOR_H
#define ZONEGENERATOR_H

#include <world/Position.h>
#include <vector>

class ZoneGenerator {

public:
  typedef std::vector<world::Position> Zone;

  /// \brief Constructor
  ZoneGenerator();

  /// \brief Create zone with size vertex
  /// \param size : Number of vertex
  void createZone(int size);

  /// \brief Add object in zone
  void addObject();

  // \brief Calculate the y coordinate according to the equation of line AB, as a function of an x coordinate
  float calculateY(const world::Position &posA, const world::Position &posB,
      float xC);

  Zone objects();

  Zone vertexs();

private:
  Zone _vertexs;
  Zone _objects;
};

#endif /* ZONEGENERATOR_H */
