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
/// \file   Ressource.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 21 septembre 2020, 19:30
///

#ifndef RESSOURCE_H
#define RESSOURCE_H

/// \brief Represents a ressource stack
class Stack {
public:
  
  /// \brief Enum of all ressources kind
  enum Ressource {
    Invalid,
    Wood,
    Rock
  };
  
private:
  
  int       _size;
  Ressource _type;
  
public:
  
  /// \brief Default Constructor, build invalid ressource
  Stack();
  /// \brief Create a ressource of given type and size
  Stack(Ressource type, int size);
  
  /// \brief return quantity of ressources inside the stack
  int size() const;
  /// \brief try to remove 'qty' of ressource from the stack
  /// \return quantity removed : min(size, qty)
  int reduce(int qty);
  
  /// \brief return stack type
  Ressource type() const;
  
  /// \brief return true if the stack is empty
  bool empty() const;
};

#endif /* RESSOURCE_H */
