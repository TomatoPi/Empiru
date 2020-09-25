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
/// \file   SDLHandler.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 septembre 2020, 21:55
/// \brief Wrapper for SDL_Events handling
///

#include "SDLHandler.h"
#include "utils/hex/Conversion.h"
#include "utils/log.h"

/// \brief Size of border (in pixels) used to scroll view
#define MERGE 50

/// \brief Constructor
SDLHandler::SDLHandler(AbstractCamera & c, const hex::Viewport & w, Controller & e, RenderingEngine & rdr, Window & win) :
  _camera(c),
  _worldview(w),
  _controller(e),
  _rengine(rdr),
  _window(win)
{
  
}

/// \brief Core SDLHandler's function, process all events availables
bool SDLHandler::handleSDLEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch(event.type) {
    case SDL_QUIT:
      return false;
    case SDL_KEYDOWN:
      if (!handleKeyDown(event.key)) return false;
      break;
    case SDL_KEYUP:
      handleKeyUp(event.key);
      break;
    case SDL_MOUSEBUTTONDOWN:
      handleMouseButtonDown(event.button);
      break;
    case SDL_MOUSEMOTION:
      handleMouseMovement(event.motion);
      break;
    }
  }
  return true;
}

// ---- Keyboard ---- //

/// \brief Handle keydown
bool SDLHandler::handleKeyDown(const SDL_KeyboardEvent & key) {
  // Auto reject key repeat
  if (key.repeat) return true;
  // Handle each button
  switch(key.keysym.sym) {
  case SDLK_ESCAPE:
    return false;
  case SDLK_UP:
    _camera.scrollUp();
    break;
  case SDLK_DOWN:
    _camera.scrollDown();
    break;
  case SDLK_RIGHT:
    _camera.scrollRight();
    break;
  case SDLK_LEFT:
    _camera.scrollLeft();
    break;
  case SDLK_a:
    _camera.rotateRight();
    break;
  case SDLK_e:
    _camera.rotateLeft();
    break;
  }
  return true;
}

/// \brief Handle keyup
bool SDLHandler::handleKeyUp(const SDL_KeyboardEvent & key) {
  switch(key.keysym.sym) {
  case SDLK_UP:
  case SDLK_DOWN:
    _camera.stopUDScroll();
    break;
  case SDLK_RIGHT:
  case SDLK_LEFT:
    _camera.stopLRScroll();
    break;
  }
  return true;
}

// ---- Mouse ---- //

/// \brief Handle Mouse movement
bool SDLHandler::handleMouseMovement(const SDL_MouseMotionEvent & mouse) {
  return true;
/*
  if (mouse.y <= MERGE) {
    _camera->scrollUp();
  }
  else if (mouse.y >= _window->height - MERGE) {
    _camera->scrollDown();
  }
  else {
    _camera->stopUDScroll();
  }
  
  if (mouse.x >= _window->width - MERGE) {
    _camera->scrollRight();
  }
   else if (mouse.x <= MERGE) {
    _camera->scrollLeft();
  } 
  else {
    _camera->stopLRScroll();
  }
  return true;
*/
}

/// \brief Handle mouse button down
bool SDLHandler::handleMouseButtonDown(const SDL_MouseButtonEvent & event) {
  
  hex::Axial pos;
  _worldview.fromPixel(event.x, event.y, &pos);
  _rengine.drawPixelPerfectZones();
  auto & table(_rengine.colorTable());
  SDL_LockSurface(_window.vsurface);
  SDL_Color color{255, 255, 255, 255};
  SDL_GetRGB(static_cast<uint32_t*>(_window.vsurface->pixels)[event.y * _window.vsurface->w + event.x],
      _window.vsurface->format,
      &color.r, &color.g, &color.b);
  SDL_UnlockSurface(_window.vsurface);
  //LOG_DEBUG("Color at click : %u %u %u %u\n", color.r, color.g, color.b, color.a);
  auto itr(table.find(color));
  WorldRef * obj(nullptr);
  if (itr != table.end()) {
    obj = itr->second;
  }
  
  switch(event.button){
    case SDL_BUTTON_LEFT:
      _controller.leftClickOn(pos, obj);
      break;
    case SDL_BUTTON_RIGHT:
      _controller.rightClickOn(pos, obj);
      break;
  }
  
  return true;
}