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
/// \file   PeonRenderer.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 16 septembre 2020, 12:48
/// \brief Provide PeonRenderer Object
///

#include <cassert>

#include "PeonRenderer.h"
#include "entity/peon/Peon.h"

/// Constructor
PeonRenderer::PeonRenderer(std::unique_ptr<SpriteSheet> s) : 
  _sheet(std::move(s)),
  _targets()
{
  
}

/// \brief Draw a peon on screen, with (x,y) coordinate of bottom's middle
int PeonRenderer::renderAt(
    const WorldObject * obj, 
    int ori, int x, int y,
    const HexViewport & view,
    SDL_Renderer *rdr) 
{
  const Peon *peon(static_cast<const Peon*>(obj));
  int frame = peon->hasPath() ? _targets.at(obj).update() : _targets.at(obj).restart();
  ori = (ori + 6 - peon->direction().orientation()) % 6;
  SDL_Rect r;
  r.w = _sheet->width();
  r.h = _sheet->height();
  r.x = x - r.w / 2;
  r.y = y - r.h;
  return _sheet->renderFrame(frame, ori, rdr, &r);
}

/// \brief Called when a new object associated with this renderer is created
///  may instanciate fine scope datas, like animation state
void PeonRenderer::addTarget(const WorldObject *obj) {
  auto insert(_targets.emplace(obj, Animation(7, 6)));
  assert(insert.second);
}
/// \brief Called when an object associated with this renderer is destroyed
///  may dealocate corresponding datas
void PeonRenderer::removeTarget(const WorldObject *obj) {
  auto itr(_targets.find(obj));
  assert(itr != _targets.end());
  _targets.erase(itr);
}