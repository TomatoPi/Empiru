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

#ifndef UTILS_COUNTER_H
#define UTILS_COUNTER_H

/// \brief Simple box to store animated sprite related datas
class Counter {
private:
  int _length;  ///< Total frames count
  int _cptr;    ///< Current frame counter
public:
  
  Counter() noexcept : Counter(0) {}
  
  /// \brief Create an animation
  /// \param length : frames count
  Counter(int length) noexcept :
    _length(length), _cptr(0)
  {}
  
  /// \brief Update animation's counter and return current frame index
  int tick() noexcept {
    if (_length == 0) {
      return 0;
    }
    if (++_cptr >= _length) {
      _cptr = 0;
    }
    return _cptr;
  }
  
  /// \brief Return curent's animation frame
  int value() const noexcept {
    return _cptr;
  }
  
  /// \brief Reset animation to initial frame and return 0
  int restart() noexcept {
    return _cptr = 0;
  }
};

class SlowCounter {
private:
  Counter _small;
  Counter _big;
public:
  
  /// \brief Create an animation
  /// \param length : frames count
  SlowCounter(int length, int latency) noexcept :
    _small(latency), _big(length)
  {}
  
  /// \brief Update animation's counter and return current frame index
  int tick() noexcept {
    if (_small.tick() == 0) {
      return _big.tick();
    }
    return _big.value();
  }
  
  /// \brief Return curent's animation frame
  int value() const noexcept {
    return _big.value();
  }
  
  /// \brief Reset animation to initial frame and return 0
  int restart() noexcept {
    _small.restart();
    return _big.restart();
  }
};

#endif /* UTILS_COUNTER_H */
