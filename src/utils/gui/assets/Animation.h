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
/// \file   Animation.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 17 septembre 2020, 17:52
/// \brief Simple box to store animated sprite related datas
///

#ifndef ANIMATION_H
#define ANIMATION_H

/// \brief Simple box to store animated sprite related datas
class Animation {
private:
  int _frame;   ///< Current frame
  int _length;  ///< Total frames count
  int _delay;   ///< Duration of a frame in ticks
  int _cptr;    ///< Current frame counter
public:
  
  /// \brief Create an animation
  /// \param length : frames count
  /// \param delay  : frame duration
  Animation(int length, int delay);
  
  /// \brief Update animation's counter and return current frame index
  int update();
  /// \brief Reset animation to initial frame and return 0
  int restart();
};

#endif /* ANIMATION_H */
