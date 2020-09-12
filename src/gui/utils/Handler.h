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
/// \file   Handler.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 septembre 2020, 21:55
///

#ifndef HANDLER_H
#define HANDLER_H


#include <SDL2/SDL_events.h>
#include "Window.h"

#include "gui/impl/Camera.h"
#include "world/utils/World.h"
#include "../../engine/controller.h"
#include "utils/log.h"

class Handler {
public:
  Handler(Camera *c, Window *w, World *world, Controller *controller);
  bool handleSDLEvents();
  
private:
  
  bool handleKeyDown(const SDL_KeyboardEvent & event);
  bool handleKeyUp(const SDL_KeyboardEvent & event);
  bool handleMouseButtonLeftDown(const FlatHexPosition & pos);
  bool handleMouseMovement(const SDL_MouseMotionEvent & event);
  bool handleMouseButtonDown(const SDL_MouseButtonEvent & event);
  bool handleMouseButtonRightDown(const FlatHexPosition & pos);
  
  Camera *_camera;
  Window *_window;
  World *_world;
  Controller *_controller;
};

#endif /* HANDLER_H */

