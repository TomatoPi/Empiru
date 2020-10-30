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
/// \file   GenericRTarget.h
/// \author tomato
///
/// \date 29 oct. 2020 03:55:37
///
#ifndef SOURCES_BUILTIN_RENDER_GENERICRTARGET_H_
#define SOURCES_BUILTIN_RENDER_GENERICRTARGET_H_

#include <render/ATarget.h>

namespace render {

namespace helpers {

template<typename Blitter>
class GenericRTarget: public ::render::ATarget {
private:
  Blitter _blitter;
public:
  GenericRTarget(const Pointer &ptr) noexcept :
      ATarget(ptr) {
  }
  virtual ~GenericRTarget() = default;

  void updateBlitRect(const gui::Pixel &tile) noexcept override final {
    _blitrect = _blitter(_viewpos,
        gui::Pixel { _asset->sheet->width(), _asset->sheet->height() }, tile);
  }
  void draw() override {
    _asset->sheet->renderFrame(0, _orientation, &_blitrect);
  }
  void drawMask(const SDL_Color &color) override {
    _asset->mask->setColorMod(color);
    _asset->mask->renderFrame(0, _orientation, &_blitrect);
  }

  struct Builder: public ATarget::Builder {
    Blitter blitter;
    virtual ~Builder() noexcept = default;
    virtual void operator()(ATarget &target) noexcept {
      this->ATarget::Builder::operator ()(target);
      static_cast<GenericRTarget<Blitter>&>(target)._blitter = blitter;
    }
  };
};

}  // namespace helpers

}  // namespace render

#endif /* SOURCES_BUILTIN_RENDER_GENERICRTARGET_H_ */
