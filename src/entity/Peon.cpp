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
 * File:   peon.cpp
 * Author: Alexis CORREIA HENRIQUES <alex2ikangame@gmail.com>
 * 
 * Created on 10 septembre 2020, 16:08
 */

#include "Peon.h"

Peon::Peon(const FlatHexPosition & pos) : 
  WorldObject(pos), 
  _target(pos),
  _dir()
{
  
}

const FlatHexPosition & Peon::targetPos() const {
  return _target;
}
const FlatHexPosition & Peon::direction() const {
  return _dir;
}

void Peon::setTargetPos(const FlatHexPosition & pos){
  _target = pos;
  _dir = FlatHexPosition(this->pos(), _target).unit();
}
