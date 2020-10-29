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
/// \file   log.h
/// \author tomato
///
/// \date 28 oct. 2020 20:45:03
///
#ifndef LIBS_LOG_LOG_H_
#define LIBS_LOG_LOG_H_

#include <string_view>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

namespace LOG {

enum class Level : uint8_t {
  Error, Warning, Info, Debug
};

static Level LogLevel = Level::Debug;

template<typename A>
void print(std::ostream &stream, A &&a) noexcept {
  stream << a << std::endl;
}

template<typename A, typename ...Args>
void print(std::ostream &stream, A &&a, Args &&... args) noexcept {
  stream << a << " ";
  print(stream, args...);
}

template<typename A, typename ...Args>
void begin(std::ostream &stream, A &&a, Args &&...args) noexcept {
  auto now = std::chrono::system_clock::to_time_t(
      std::chrono::system_clock::now());
  print(stream, std::put_time(std::localtime(&now), "%T"), std::forward<A>(a),
      std::forward<Args>(args)...);
}

template<typename ...Args>
void error(Args &&... args) noexcept {
  begin(std::cerr, ": ERROR   :", std::forward<Args>(args)...);
}

template<typename ...Args>
void warning(Args &&... args) noexcept {
  if (LogLevel >= Level::Warning) {
    begin(std::cerr, ": WARNING :", std::forward<Args>(args)...);
  }
}

template<typename ...Args>
void info(Args &&... args) noexcept {
  if (LogLevel >= Level::Info) {
    begin(std::cout, ": INFO    :", std::forward<Args>(args)...);
  }
}

template<typename ...Args>
void debug(Args &&... args) noexcept {
  if (LogLevel >= Level::Debug) {
    begin(std::cout, ": DEBUG   :", std::forward<Args>(args)...);
  }
}

inline void IncreaseLog() noexcept {
  if (LogLevel < Level::Debug) {
    LogLevel = static_cast<Level>(1 + static_cast<uint8_t>(LogLevel));
    begin(std::cout, "Set LogLevel to :", static_cast<uint8_t>(LogLevel));
  }
}

inline void DecreaseLog() noexcept {
  if (Level::Error < LogLevel) {
    LogLevel = static_cast<Level>(-1 + static_cast<uint8_t>(LogLevel));
    begin(std::cout, "Set LogLevel to :", static_cast<uint8_t>(LogLevel));
  }
}
}

#endif /* LIBS_LOG_LOG_H_ */
