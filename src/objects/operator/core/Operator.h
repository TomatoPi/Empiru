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
/// \file   Operator.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 21 octobre 2020, 15:27
///

#ifndef OPERATOR_H
#define OPERATOR_H

#include "core/Object.h"
#include "core/Builder.h"

/// \brief Operators are special objects which are callables
class Operator : public core::Object {
  public:

  Operator() noexcept = default;
  virtual ~Operator() noexcept = default;
  
  /// Make sure that operators override this method
  bool update() noexcept override = 0;

  class Builder : public core::Builder {
  public:
    Builder() noexcept : core::Builder() {}
    void operator() (core::Pointer& ptr) noexcept override {
      this->core::Builder::operator() (ptr);
    }
  };
};

#endif /* OPERATOR_H */

