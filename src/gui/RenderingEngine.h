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
/// \file   WorldRenderer.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 10 septembre 2020, 14:56
/// \brief Core object of rendering engine
///

#ifndef WORLDRENDERER_H
#define WORLDRENDERER_H

#include <typeindex>
#include <unordered_map>
#include <map>
#include <memory>

#include "utils/gui/Window.h"
#include "utils/hex/HexViewport.h"
#include "utils/gui/AbstractRenderer.h"
#include "utils/gui/AbstractCamera.h"
#include "utils/world/WorldInterface.h"

/// \brief Object responsible of Game rendering
class RenderingEngine {
private:
  
  struct ViewPos {
    int _x, _y;
    ViewPos(int x, int y);
  };
  
  struct ViewPosCompare {
    bool operator() (const ViewPos & a, const ViewPos & b) const;
  };
  
  typedef std::unordered_map<std::type_index, AbstractRenderer*>
    RendererTable;
  typedef std::map<ViewPos, WorldObject*, ViewPosCompare> DrawStack;
  
  Window *_window;
  HexViewport *_worldView;
  AbstractCamera *_camera;
  WorldInterface *_world;
  
  RendererTable _renderers;
  DrawStack _todraw;
  
public:
  
  /// \brief Constructor
  RenderingEngine(
          Window *w, 
          HexViewport *c, 
          AbstractCamera *ac,
          WorldInterface *wo);
  
  /// \brief Add a new renderer associated with given WorldObject type
  void attachRenderer(const std::type_info & info, AbstractRenderer* rdr);
  
  /// \brief Draw EVERYTHINGS (in the world)
  void render();
};

#endif /* WORLDRENDERER_H */
