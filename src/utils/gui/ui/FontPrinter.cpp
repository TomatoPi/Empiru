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
/// \file   FontPrinter.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 28 septembre 2020, 20:32
///
#include <vector>

#include "FontPrinter.h"
#include "utils/log.h"

FontPrinter::FontPrinter(SDL_Renderer *rdr) : 
  _numbers(SpriteSheet::loadFromFile(
    "medias/sprites/ui/font/numbers.png", 1, 10, rdr)),
  _chars(nullptr)
{
}

void FontPrinter::drawStringAt(
    int x, int y, Anchor anchor,
    const std::string & str) 
{
  DrawStack stack(processString(str));
  /* move (x,y) according to anchor */
  switch (anchor) {
  case UpLeft:
    /* (x,y) is already valid */
    break;
  case UpRight:
    x -= stack.totalSize._x;
    break;
  case DownRight:
    x -= stack.totalSize._x;
    y -= stack.totalSize._y;
    break;
  case DownLeft:
    y -= stack.totalSize._y;
    break;
  case CenterRight:
    x -= stack.totalSize._x;
    y -= stack.totalSize._y / 2;
    break;
  default:
    assert(0);
  }
  /* let's get it started */
  for (auto & step : stack.stack) {
    drawStep(x, y, stack.totalSize, step);
    x += step.size._x;
  }
}

void FontPrinter::drawStep(
  int x, int y, 
  const math::Vector<int> & totalSize, 
  const DrawStep & step)
{
  SDL_Rect rect;
  rect.w = step.size._x;
  rect.h = step.size._y;
  rect.x = x;
  rect.y = y + totalSize._y - step.size._y;
  switch (step.sheet) {
  case Invalid:
    assert(0 && "Invalid Step");
    break;
  case Number:
    _numbers->renderFrame(0, step.index, &rect);
    break;
  case LowerCase:
    _chars->renderFrame(0, step.index, &rect);
    break;
  case UpperCase:
    _chars->renderFrame(1, step.index, &rect);
    break;
  }
}
  
FontPrinter::DrawStack FontPrinter::processString(const std::string & str) 
const 
{
  DrawStack stack;
  stack.stack.reserve(str.size());
  for (auto c : str) {
    DrawStep step(processChar(c));
    stack.totalSize._x += step.size._x;
    stack.totalSize._y = std::max(stack.totalSize._y, step.size._y);
    stack.stack.push_back(step);
  }
  return stack;
}

FontPrinter::DrawStep FontPrinter::processChar(char c) 
const 
{
  if ('0' <= c && c <= '9') {
    return DrawStep{
      math::Vector<int>(_numbers->width(), _numbers->height()),
      c - '0',
      Number};
  }
  if ('a' <= c && c <= 'z') {
    return DrawStep{
      math::Vector<int>(_chars->width(), _chars->height()), 
      c - 'a',
      LowerCase};
  }
  if ('A' <= c && c <= 'Z') {
    return DrawStep{
      math::Vector<int>(_chars->width(), _chars->height()), 
      c - 'A',
      UpperCase};
  }
  assert(0 && "Invalid string content");
  LOG_WRN("Invalid String content : %c\n", c);
  return DrawStep{};
}