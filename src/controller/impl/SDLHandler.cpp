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
#include "utils/hex/Viewport.h"
//#include "entity/buildings/house/House.h"
//#include "entity/buildings/warehouse/Warehouse.h"

/// \brief Size of border (in pixels) used to scroll view
#define MERGE 50

/// \brief Constructor
SDLHandler::SDLHandler(
          AbstractCamera & c,
          const hex::Viewport & v,
          Controller & e,
          ControlPannel & pan,
          PixelPerfectClicker & click) 
noexcept :
  _camera(c),
  _viewport(v),
  _controller(e),
  _controlPannel(pan),
  _clicker(click),
      
  _mouseMoved(false),
  _mouseX(0), _mouseY(0)
{
  
}
  
void SDLHandler::beginTick() {
  _mouseMoved = false;
}
void SDLHandler::endTick() {
  if (_mouseMoved) {
    hex::Axial pos;
    _viewport.fromPixel(_mouseX, _mouseY, &pos);
    _controller.cursorMoved(pos, _mouseX, _mouseY);
  }
}

/// \brief Core SDLHandler's function, process all events availables
bool SDLHandler::handleSDLEvents() {
  SDL_Event event;
  beginTick();
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
  endTick();
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
  case SDLK_h:
    //_controller.selectConstructionGhost(typeid(House));
    break;
  case SDLK_j:
    //_controller.selectConstructionGhost(typeid(Warehouse));
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
  _mouseMoved = true;
  _mouseX = mouse.x;
  _mouseY = mouse.y;
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
  _viewport.fromPixel(event.x, event.y, &pos);
  _clicker.updateClickZones();
  Pointer obj(_clicker.objectAt(event.x, event.y));
  
  switch(event.button){
    case SDL_BUTTON_LEFT:
      if (_viewport.isInView(event.x, event.y))
        _controller.leftClickOn(pos, obj);
      break;
    case SDL_BUTTON_RIGHT:
      if (_viewport.isInView(event.x, event.y))
        _controller.rightClickOn(pos, obj);
      break;
  }
  
  return true;
}