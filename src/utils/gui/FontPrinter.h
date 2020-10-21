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
/// \file   FontPrinter.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 28 septembre 2020, 20:12
///

#ifndef FONTPRINTER_H
#define FONTPRINTER_H

#include "utils/math/Vector.h"
#include "utils/assets/SpriteSheet.h"

#include <vector>
#include <string>

class FontPrinter {
public:
  
  enum Anchor {
    UpLeft,
    UpRight,
    DownRight,
    DownLeft,
    CenterRight
  };
  
public:
  
  FontPrinter(SDL_Renderer *rdr);
  ~FontPrinter() noexcept = default;
  
  void drawStringAt(
    int x, int y, Anchor anchor,
    const std::string & str);
  
private:
  
  std::shared_ptr<SpriteSheet> _numbers;
  std::shared_ptr<SpriteSheet> _chars;
  
  enum Sheet {
    Invalid,
    Number,
    LowerCase,
    UpperCase,
    Space,
    Special
  };
  
  struct DrawStep {
    math::Vector<int> size;
    int               index;
    Sheet             sheet;
  };
  
  struct DrawStack {
    std::vector<DrawStep> stack;
    math::Vector<int>     totalSize;
  };
  
  DrawStack processString(const std::string & str) const;
  DrawStep processChar(char c) const;
  
  void drawStep(
    int x, int y, 
    const math::Vector<int> & totalSize, 
    const DrawStep & step);
};

#endif /* FONTPRINTER_H */

