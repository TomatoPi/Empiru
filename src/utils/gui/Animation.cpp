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
/// \file   Animation.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 17 septembre 2020, 17:52
///

#include "Animation.h"

/// \brief Create an animation
/// \param length : frames count
/// \param delay  : frame duration
Animation::Animation(int length, int delay) :
  _frame(0), _length(length), _delay(delay), _cptr(0)
{
  
}

/// \brief Update animation's counter and return current frame index
int Animation::update() {
  _cptr = (_cptr+1) % _delay;
  if (_cptr == 0) 
    _frame = (_frame+1) % _length;
  return _frame;
}
/// \brief Reset animation to initial frame and return 0
int Animation::restart() {
  return _cptr = _frame = 0;
}