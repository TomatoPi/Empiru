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
/// \file   PixelPerfectBridge.cpp
/// \author tomato
///
/// \date 27 oct. 2020 22:01:14
///
#include <render/impl/PixelPerfectBridge.h>

namespace render {
namespace impl {

PixelPerfectBridge::PixelPerfectBridge(const gui::Viewport &view, int w, int h) :
    _table(), _view(view), _surface(nullptr), _renderer(nullptr), _cptr(0) {
  /* create virtual surface and software renderer */
  _surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
  if (!_surface) {
    throw std::runtime_error(SDL_GetError());
  }
  /* create the software renderer associated with surface */
  _renderer = SDL_CreateSoftwareRenderer(_surface);
  if (!_renderer) {
    SDL_free(_surface);
    throw std::runtime_error(SDL_GetError());
  }
}

std::pair<world::Position, game::EUID> PixelPerfectBridge::at(
    const gui::Pixel &pix) noexcept {
  Subject<Events::BridgeNeedUpdate>::notify(); // @suppress("Function cannot be resolved")
  SDL_LockSurface(_surface);
  SDL_Color color { 255, 255, 255, 255 };
  SDL_GetRGB(
      static_cast<uint32_t*>(_surface->pixels)[pix._y * _surface->w + pix._x],
      _surface->format, &color.r, &color.g, &color.b);
  SDL_UnlockSurface(_surface);
  auto itr(_table.find(color));
  if (itr != _table.end()) {
    return {_view.fromPixel(pix), itr->second};
  }
  return {_view.fromPixel(pix), game::EUID()};
}
world::Position PixelPerfectBridge::fromPixel(const gui::Pixel &pix) noexcept {
  return _view.fromPixel(pix);
}
bool PixelPerfectBridge::isInView(const gui::Pixel& pix) noexcept {
  return _view.isInView(pix);
}

void PixelPerfectBridge::clearTable() noexcept {
  // Clear the mask
  SDL_SetRenderDrawColor(_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(_renderer);
  // Iniitalise unique colors
  _table.clear();
  _cptr = 1;
}
void PixelPerfectBridge::addObject(ATarget &target,
    const gui::Viewport &view) noexcept {
  SDL_Color color;
  color.r = (_cptr & 0x000000FF) >> 0;
  color.g = (_cptr & 0x0000FF00) >> 8;
  color.b = (_cptr & 0x00FF0000) >> 16;
  color.a = 255;
  // Get correct renderer and use it
  target.drawMask(color);
  _table.emplace(color, target.entity());
  _cptr += 1;
}
SDL_Renderer* PixelPerfectBridge::renderer() noexcept {
  return _renderer;
}

}  // namespace impl
} /* namespace render */
