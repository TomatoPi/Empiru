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
/// \file   SDLHandler.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 septembre 2020, 21:55
/// \brief Wrapper for SDL_Events handling
///

#ifndef SDLHANDLER_H
#define SDLHANDLER_H


#include <SDL2/SDL_events.h>

#include "utils/gui/view/AbstractCamera.h"
#include "utils/hex/Viewport.h"
#include "controller/Controller.h"

/// \brief Wrapper object for SDL_Events handling
class SDLHandler {
private:
  
  AbstractCamera    &_camera;    ///< Worldview controller
  const hex::Viewport &_worldview; ///< Bridge between userview and controller
  Controller        &_controller;///< The thing that do things on other things
  
public:
  
  /// \brief Constructor
  SDLHandler(AbstractCamera & c, const hex::Viewport & w, Controller & e);
  
  /// \brief Core SDLHandler's function, process all events availables
  bool handleSDLEvents();
  
private:
  
  // ---- Keyboard ---- //
  
  bool handleKeyDown(const SDL_KeyboardEvent & event);
  bool handleKeyUp(const SDL_KeyboardEvent & event);
  
  // ---- Mouse ---- //
  
  bool handleMouseMovement(const SDL_MouseMotionEvent & event);
  bool handleMouseButtonDown(const SDL_MouseButtonEvent & event);
  
};

#endif /* SDLHANDLER_H */

