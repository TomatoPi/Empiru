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
/// \file   PixelPerfectBridge.h
/// \author tomato
///
/// \date 27 oct. 2020 22:01:14
///
#ifndef SOURCES_RENDER_IMPL_PIXELPERFECTBRIDGE_H_
#define SOURCES_RENDER_IMPL_PIXELPERFECTBRIDGE_H_

#include <game/EUID.h>
#include "../ATarget.h"
#include <observer/SuperObserver.h>
#include <gui/Bridge.h>
#include <SDL2/SDL_shape.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_render.h>
#include <unordered_map>

namespace render {
namespace impl {

namespace Events {
struct BridgeNeedUpdate {
};
}

class PixelPerfectBridge final : public gui::Bridge,
    public SuperObserver::Subject<PixelPerfectBridge, Events::BridgeNeedUpdate> {
public:

  template<typename E>
  using Subject = SuperObserver::Subject<PixelPerfectBridge, E>;

  /// \brief Hash an SDL_Color according to its compenents
  struct ColorHasher {
    std::size_t operator()(const SDL_Color &c) const noexcept {
      std::size_t r(static_cast<std::size_t>(c.r));
      std::size_t g(static_cast<std::size_t>(c.g));
      std::size_t b(static_cast<std::size_t>(c.b));
      std::size_t a(static_cast<std::size_t>(c.a));
      return (r << 24) ^ (g << 16) ^ (b << 8) ^ a;
    }
  };
  struct ColorEquals {
    bool operator()(const SDL_Color &a, const SDL_Color &b) const noexcept {
      return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
    }
  };

private:

  using ColorTable = std::unordered_map<SDL_Color,game::EUID,ColorHasher,ColorEquals>;
  ColorTable _table;

  SDL_Surface *_surface;   ///< Virtual drawing surface (owned)
  SDL_Renderer *_renderer; ///< Renderer associated with vsurface (owned)
  uint32_t _cptr;

public:

  /// \throw runtime_error if failed create renderer or surface
  PixelPerfectBridge(int w, int h);
  virtual ~PixelPerfectBridge() noexcept = default;

  game::EUID objectAt(const gui::Pixel&) noexcept override;

  void clearTable() noexcept;
  void addObject(ATarget &target, const gui::Viewport &view) noexcept;
};

}  // namespace impl
} /* namespace render */

#endif /* SOURCES_RENDER_IMPL_PIXELPERFECTBRIDGE_H_ */
