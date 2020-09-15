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

#include "utils/gui/Window.h"
#include "utils/hex/HexViewport.h"
#include "utils/gui/AbstractRenderer.h"
#include "world/World.h"

/// \brief Object responsible of Game rendering
class RenderingEngine {
private:
  
  Window *_window;
  HexViewport *_worldView;
  World *_world;
  AbstractRenderer *_tilerdr;
  AbstractRenderer *_peonrdr;
  
public:
  
  /// \brief Constructor
  RenderingEngine(
          Window *w, 
          HexViewport *c, 
          World *wo, 
          AbstractRenderer *t,
          AbstractRenderer *p);
  
  /// \brief Draw EVERYTHINGS (in the world)
  void render();
};

#endif /* WORLDRENDERER_H */
