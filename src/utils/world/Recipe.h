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
/// \file   Recipe.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 6 octobre 2020, 09:06
///

#ifndef RECIPE_H
#define RECIPE_H

#include <initializer_list>
#include <map>
#include <cassert>
#include "Ressource.h"

class Recipe {
public:
  
  typedef std::map<Stack::Ressource,int> RecipeTable;
  
private:
  
  RecipeTable _recipe;
  RecipeTable _supplied;
  
protected:
  
  void setRecipe(const std::initializer_list<Stack>& list) noexcept {
    assert(_recipe.size() == 0);
    assert(_supplied.size() == 0);
    for (auto& stack : list) {
      assert(0 < stack.size());
      assert(_recipe.find(stack.type()) == _recipe.end());
      _recipe[stack.type()] = stack.size();
      _supplied[stack.type()] = 0;
    }
  }
  
public:
  
  Recipe() noexcept : _recipe(), _supplied() {}
  virtual ~Recipe() = default;
    
  const RecipeTable& recipe() const noexcept {
    return _recipe;
  }
  
  const RecipeTable& supplied() const noexcept {
    return _supplied;
  }
  
  bool isFilled() const noexcept {
    for (const auto& pair : _recipe) {
      int supplied = _supplied.at(pair.first);
      assert(supplied <= pair.second);
      if (supplied != pair.second) {
        return false;
      }
    }
    return true;
  }
  
  bool need(const Stack& stack) const noexcept {
    return _recipe.find(stack.type()) != _recipe.end()
        && _supplied.at(stack.type()) < _recipe.at(stack.type());
  }
  
  Stack supply(Stack stack) noexcept {
    assert(_recipe.find(stack.type()) != _recipe.end());
    int needed(_recipe[stack.type()] - _supplied[stack.type()]);
    int qty(stack.reduce(needed));
    _supplied[stack.type()] += qty;
    assert(_supplied[stack.type()] <= _recipe[stack.type()]);
    return stack;
  }
};


#endif /* RECIPE_H */

