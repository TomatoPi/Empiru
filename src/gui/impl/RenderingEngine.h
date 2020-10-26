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
/// \file   RenderingEngine.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 10 septembre 2020, 14:56
/// \brief Core object of rendering engine
///

#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <typeindex>
#include <unordered_map>
#include <map>
#include <vector>

#include "utils/math/Vector.h"
#include "utils/hex/Viewport.h"
#include "utils/gui/Window.h"
#include "gui/core/Types.h"
#include "gui/core/AbstractCamera.h"
#include "gui/core/PixelPerfectClicker.h"
#include "gui/core/AbstractRenderer.h"
#include "world/core/IWorldMap.h"
#include "core/Observer.h"
#include "objects/decorator/decorators/drawable/Drawable.h"

namespace gui {
  /// \brief Object responsible of Game rendering
  class RenderingEngine : public IPixelPerfectClicker {
  public:

    /// \brief Hash an SDL_Color according to its compenents
    struct ColorHasher {
      std::size_t operator() (const SDL_Color & c) const noexcept {
        std::size_t r(static_cast<std::size_t>(c.r));
        std::size_t g(static_cast<std::size_t>(c.g));
        std::size_t b(static_cast<std::size_t>(c.b));
        std::size_t a(static_cast<std::size_t>(c.a));
        return (r << 24) ^ (g << 16) ^ (b << 8) ^ a;
      }
    };
    struct ColorEquals {
      bool operator() (const SDL_Color & a, const SDL_Color & b) const noexcept {
        return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
      }
    };

  private:

    using ColorTable = std::unordered_map<SDL_Color,core::Pointer,ColorHasher,ColorEquals>;

    /// \brief Table used to make the rendering engine blind on what is in the world
    ///   One must register each kind of object with it associated renderer
    using RendererTable = std::unordered_map<std::type_index,ARenderer*>;

    /// \brief List used to store the sorted list of objects beeing drawn 
    ///   during this frame
    /// Sorting is done on ascending y to ensure that objects away from camera
    ///   are drawn behind
    using DrawStack = std::multimap<Pixel,core::Pointer,Pixel::AscYCompare>;

    using Target = decorators::ADrawable;
    
    Window &                _window;    ///< Obvious
    const hex::Viewport &   _worldView; ///< Bridge between game and user
    const AbstractCamera &  _camera;    ///< View controller
    const IWorldMap &       _world;     ///< Obvious too

    RendererTable _renderers; ///< Table of {ObjectType, Associated renderer}
    DrawStack     _drawstack; ///< Ascending Y sorted list of objects beeing drawn during this frame
    ColorTable    _colors;
    std::vector<core::Pointer> _changeds;
    std::vector<Pixel> _viewables;

  public:

    /// \brief Constructor
    RenderingEngine(
        Window&               win,
        const hex::Viewport&  vp,
        const AbstractCamera& cam,
        const IWorldMap& wo);
    virtual ~RenderingEngine() noexcept = default;

    /// \brief Add a new renderer associated with given WorldObject type
    void attachRenderer(const std::type_info& info, ARenderer* rdr);

    /// \brief Draw EVERYTHINGS (in the world)
    void render();

    /// \brief Draw every sized object 
    virtual void updateClickZones();
    /// \brief Return object at x,y or nullptr if none
    virtual core::Pointer entityAt(int x, int y) const noexcept;

  private:
    
    void newTarget(core::Pointer ptr) noexcept;
    void targetDeleted(core::Pointer ptr) noexcept;
    void updateDrawStack() noexcept;
    void removeFromStack(const core::Pointer& ptr) noexcept;

    /// \brief renturn the renderer for specified type 
    ///   or throw if type not registered
    ARenderer* getrdr(const core::Pointer& obj);
  };
}
#endif /* RENDERENGINE_H */
