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
 * File:   peon.h
 * Author: Alexis CORREIA HENRIQUES <alex2ikangame@gmail.com>
 *
 * Created on 10 septembre 2020, 16:08
 */


#ifndef PEON_H
#define PEON_H

#include "utils/hex/HexCoords.h"
#include "utils/world/WorldObject.h"

class Peon : public WorldObject {
  private:
    
    FlatHexPosition _target;
    FlatHexPosition _dir;
    
  public:
    
    Peon(const FlatHexPosition & pos);
    
    std::string toString() const;

    const FlatHexPosition & targetPos() const;
    const FlatHexPosition & direction() const;
    
    void setTargetPos(const FlatHexPosition & pos, bool updateDir=true);
};

#endif /* PEON_H */