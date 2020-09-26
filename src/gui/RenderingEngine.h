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

#include "utils/math/Vector.h"
#include "utils/hex/Viewport.h"
#include "utils/gui/view/Window.h"
#include "utils/gui/view/AbstractCamera.h"
#include "utils/gui/renderer/AbstractRenderer.h"
#include "utils/world/WorldInterface.h"

/// \brief Object responsible of Game rendering
class RenderingEngine {
public:
  
  /// \brief Hash an SDL_Color according to its compenents
  struct ColorHasher {
    std::size_t operator() (const SDL_Color & c) const;
  };
  struct ColorEquals {
    bool operator() (const SDL_Color & a, const SDL_Color & b) const;
  };
  
  typedef std::unordered_map<SDL_Color, WorldRef *, ColorHasher, ColorEquals>
  ColorTable;
  
private:
  
  /// \brief Table used to make the rendering engine blind on what is in the world
  ///   One must register each kind of object with it associated renderer
  typedef std::unordered_map<std::type_index, AbstractRenderer&> RendererTable;
  /// \brief Represent a pixel on the screen
  typedef math::Vector<int> Pixel;
  /// \brief List used to store the sorted list of objects beeing drawn 
  ///   during this frame
  /// Sorting is done on ascending y to ensure that objects away from camera
  ///   are drawn behind
  typedef std::multimap<Pixel, WorldRef *, Pixel::AscYCompare> DrawStack;
  
  Window &                _window;    ///< Obvious
  const hex::Viewport &   _worldView; ///< Bridge between game and user
  const AbstractCamera &  _camera;    ///< View controller
  const WorldInterface &  _world;     ///< Obvious too
  
  RendererTable _renderers; ///< Table of {ObjectType, Associated renderer}
  DrawStack     _drawstack; ///< Ascending Y sorted list of objects beeing drawn during this frame
  ColorTable    _colors;
  uint8_t       _r, _g, _b;
  
public:
  
  /// \brief Constructor
  RenderingEngine(
      Window &               win,
      const hex::Viewport &  vp,
      const AbstractCamera & cam,
      const WorldInterface & wo);
  
  /// \brief Add a new renderer associated with given WorldObject type
  void attachRenderer(const std::type_info & info, AbstractRenderer & rdr);
  
  /// \brief Add a new target to the rendering engine
  void addTarget(const WorldRef * obj);
  /// \brief Remove a target from the rendering engine
  void removeTarget(const WorldRef * obj);
  
  /// \brief Draw EVERYTHINGS (in the world)
  void render();
  /// \brief Draw every sized object 
  void drawPixelPerfectZones();
  
  /// \brief Return last computed color table
  const ColorTable & colorTable() const;
};

#endif /* RENDERENGINE_H */
