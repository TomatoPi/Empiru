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
/// \file   RenderingEngine.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 10 septembre 2020, 14:56
/// \brief Core object of rendering engine
///

#include <cassert>

#include "RenderingEngine.h"
#include "utils/log.h"

std::size_t RenderingEngine::ColorHasher::operator() (const SDL_Color & c) const {
  std::size_t r(static_cast<std::size_t>(c.r));
  std::size_t g(static_cast<std::size_t>(c.g));
  std::size_t b(static_cast<std::size_t>(c.b));
  std::size_t a(static_cast<std::size_t>(c.a));
  return (r << 24) ^ (g << 16) ^ (b << 8) ^ a;
}
bool RenderingEngine::ColorEquals::operator() (const SDL_Color & a, const SDL_Color & b) const {
  return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

RenderingEngine::RenderingEngine(
    Window &               win,
    const hex::Viewport &  vp,
    const AbstractCamera & cam,
    const WorldInterface & wo) : 
  _window(win),
  _worldView(vp),
  _camera(cam),
  _world(wo),
  _renderers(),
  _drawstack()
{
}

/// \brief Add a new renderer associated with given WorldObject type
void RenderingEngine::attachRenderer(
  const std::type_info & info, 
  AbstractRenderer & rdr) 
{
  bool success(_renderers.emplace(std::type_index(info), rdr).second);
  assert(success);
}

/// \brief Add a new target to the rendering engine
void RenderingEngine::addTarget(const WorldRef * obj) {
  _renderers.at(std::type_index(typeid(**obj))).addTarget(obj);
}
/// \brief Remove a target from the rendering engine
void RenderingEngine::removeTarget(const WorldRef * obj) {
  _renderers.at(std::type_index(typeid(**obj))).removeTarget(obj);
}

void RenderingEngine::render() {
  hex::Axial anchor, pos, vx, vy;
  // Compute anchor position and drawsteps
  _worldView.upLeftCorner(&anchor);
  _worldView.viewPortAxis(&vx, &vy);
  // Move one tile away to always draw left and up tiles
  anchor = hex::Axial(anchor - vx*2 - vy*2).tile();
  // Compute render situation
  int x, y, xx, yy,
      dx(_worldView.tileWidth() * 0.75), 
      dy(_worldView.tileHeight());
  // Get tile renderer
  AbstractRenderer & tilerdr(
        _renderers.find(std::type_index(typeid(Tile)))->second);
  _drawstack.clear();
  // Get initial position and start
  for (
      xx = -_worldView.tileWidth() *2;
      (xx-dx) - _worldView.tileWidth() < _window.width;
      xx += dx, anchor = anchor +vx
      )
  {
    for (
        pos = anchor, yy = -_worldView.tileHeight() *2; 
        (yy-dy) - _worldView.tileHeight() < _window.height ;
        yy += dy, pos = pos +vy
        )
    {
      // Render tile pos at (x, y+offx[!!flip])
      if (_world.isOnMap(pos)) {
        _worldView.toPixel(pos.tile(), &x, &y);
        if (tilerdr.renderAt(nullptr, _camera.getOrientation(), 
            x, y, _worldView, _window.renderer)) 
        {
          LOG_ERROR("Failed draw tile : %s\n", SDL_GetError());
          OUPS();
        }
        
        auto vec(_world.getContentAt(pos));
        if (vec) {
          for (auto & obj : *vec) {
            _worldView.toPixel((**obj).pos(), &x, &y);
            _drawstack.emplace(Pixel(x, y), obj);
          }
        }
      }
    }
  } //< for each tile
  
  // Draw all entities
  for (auto & itr : _drawstack) {
    const WorldRef * obj(itr.second);
    // Get correct renderer and use it
    if (int err = _renderers.find(std::type_index(typeid(**obj)))->second
        .renderAt(
            obj,
            _camera.getOrientation(), 
            itr.first._x, itr.first._y, _worldView, _window.renderer))
    {
      LOG_ERROR("Failed draw object : %d : %s\n", err, SDL_GetError());
      OUPS();
    }
  }
}

/// \brief Draw every sized object 
void RenderingEngine::drawPixelPerfectZones() {
  // Clear the mask
  SDL_SetRenderDrawColor(_window.vrenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(_window.vrenderer);
  // Iniitalise unique colors
  _colors.clear();
  uint32_t cptr(1);
  // Draw is made according to last drawstack
  for (auto & itr : _drawstack) {
    WorldRef * obj(itr.second);
    if ((**obj).sizeClass() == WorldObject::SHollow) {
      continue;
    }
    SDL_Color color;
    color.r = (cptr & 0x000000FF) >> 0;
    color.g = (cptr & 0x0000FF00) >> 8;
    color.b = (cptr & 0x00FF0000) >> 16;
    color.a = 255;
    // Get correct renderer and use it
    if (int err = _renderers.find(std::type_index(typeid(**obj)))->second
        .renderAt(
            obj,
            _camera.getOrientation(), 
            itr.first._x, itr.first._y, _worldView, _window.vrenderer,
            color))
    {
      LOG_ERROR("Failed draw object : %d : %s\n", err, SDL_GetError());
      OUPS();
    }
    _colors.emplace(color, obj);
    cptr += 1;
  }
}
const RenderingEngine::ColorTable & RenderingEngine::colorTable() const {
  return _colors;
}