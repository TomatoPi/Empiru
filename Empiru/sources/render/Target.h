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
/// \file   Renderable.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 27 oct. 2020 15:57:34
///
#ifndef SOURCES_RENDER_TARGET_H_
#define SOURCES_RENDER_TARGET_H_

#include "world/Position.h"
#include "gui/Pixel.h"
#include "Asset.h"
/// \todo Replace this concrete include with an interface
#include "gui/impl/Viewport.h"

#include <observer/SuperObserver.h>
#include <alloc/Pointer.h>

namespace render {

namespace Events {
struct TargetMoved {
};
struct TargetRotated {
};
}

class ATarget: public SuperObserver::Subject<ATarget, Events::TargetMoved,
    Events::TargetRotated> {
public:

  template<typename E>
  using Subject = SuperObserver::Subject<ATarget, E>; // @suppress("Invalid template argument")
  using Pointer = alloc::SmartPointer<ATarget>;

private:
  Pointer _this;
  std::shared_ptr<Asset> _asset;
  world::Position _worldpos;
  gui::Pixel _viewpos;
  int _orientation;
public:

  ATarget() noexcept = delete;
  ATarget(const Pointer &ptr) noexcept :
      _this(ptr), _worldpos(), _viewpos(), _orientation() {
  }
  virtual ~ATarget() noexcept = default;

  const Pointer& ptr() const noexcept {
    return _this;
  }

  const gui::Pixel& viewpos() const noexcept {
    return _viewpos;
  }
  void viewpos(const gui::Pixel &p) noexcept {
    _viewpos = p;
  }

  int orientation() const noexcept {
    return _orientation;
  }
  void orientation(int o) noexcept {
    _orientation = o;
    Subject<Events::TargetRotated>::notify(); // @suppress("Function cannot be resolved")
  }

  const world::Position& worldpos() const noexcept {
    return _worldpos;
  }
  void worldpos(const world::Position &p) noexcept {
    _worldpos = p;
    Subject<Events::TargetMoved>::notify(); // @suppress("Function cannot be resolved")
  }

  virtual void draw(const gui::Viewport &view) = 0;
  virtual void drawMask(const gui::Viewport &view, const SDL_Color &color) = 0;

  struct Builder {
    std::shared_ptr<Asset> asset;
    world::Position pos;
    int ori;
    virtual ~Builder() noexcept = default;
    virtual void operator()(Pointer &ptr) noexcept {
      ptr->_asset = asset;
      ptr->_worldpos = pos;
      ptr->_orientation = ori;
    }
  };
};
} /* render */

#endif /* SOURCES_RENDER_TARGET_H_ */
