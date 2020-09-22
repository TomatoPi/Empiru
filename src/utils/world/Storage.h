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
/// \file   Storage.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 22 septembre 2020, 09:25
///

#ifndef STORAGE_H
#define STORAGE_H

#include "Ressource.h"
#include <unordered_set>
#include <string>

class Storage {
private:
  
  typedef std::unordered_set<Stack, StackTypeHash, StackTypeEqual> StackList;
  StackList _storage;
  
public:
  
  /// \brief Construct a storage
  Storage();
  /// \brief Make class polymorphic
  virtual ~Storage() = default;
  
  /// \brief add given stack to the storage
  void addToStorage(const Stack & stack);
  
  std::string content_str() const;
};

#endif /* STORAGE_H */
