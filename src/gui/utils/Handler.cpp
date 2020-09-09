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
/// \file   Handler.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 9 septembre 2020, 21:55
///

#include "Handler.h"
#include "utils/log.h"

#define merge 50

Handler::Handler(HexCamera *c) :
  _camera(c)
{
  
}

bool Handler::handleSDLEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch(event.type) {
    case SDL_QUIT:
      return false;
    case SDL_KEYDOWN:
      return handleKeyDown(event.key);
    case SDL_KEYUP:
      return handleKeyUp(event.key);
    case SDL_MOUSEBUTTONDOWN:
      return handleMouseButtonDown(event.button);
    case SDL_MOUSEMOTION:
      return handleMouseMovement(event.motion);
    }
  }
  return true;
}

bool Handler::handleMouseMovement(const SDL_MouseMotionEvent & mouse) {
  if (mouse.y <= merge) {
    _camera->scrollUp();
  }
  else if (mouse.y >=1080 - merge) {
    _camera->scrollDown();
  }
  else {
    _camera->stopUDScroll();
  }
   if (mouse.x >= 1920 - merge) {
    _camera->scrollRight();
  }
   else if (mouse.x <= merge) {
    _camera->scrollLeft();
  } 
   else {
     _camera->stopLRScroll();
   }
  return true;
}

bool Handler::handleKeyDown(const SDL_KeyboardEvent & key) {
  switch(key.keysym.sym) {
    case SDLK_ESCAPE:
      return false;
    case SDLK_UP:
      _camera->scrollUp();
      break;
    case SDLK_DOWN:
      _camera->scrollDown();
      break;
    case SDLK_RIGHT:
      _camera->scrollRight();
      break;
    case SDLK_LEFT:
      _camera->scrollLeft();
      break;
  }
  return true;
}

bool Handler::handleKeyUp(const SDL_KeyboardEvent & key) {
  switch(key.keysym.sym) {
    case SDLK_UP:
    case SDLK_DOWN:
      _camera->stopUDScroll();
      break;
    case SDLK_RIGHT:
    case SDLK_LEFT:
      _camera->stopLRScroll();
      break;
  }
  return true;
}

bool Handler::handleMouseButtonDown(const SDL_MouseButtonEvent & event) {
  LOG_TODO("Fonction temporaire pouet\n");
  FlatHexPosition pos;
  _camera->fromPixel(event.x, event.y, &pos);
  LOG_DEBUG("Pouet : %s\n", pos.toString().c_str());
  pos.convert(FlatHexPosition::OddQOffset);
  LOG_DEBUG("Pouat : %s\n", pos.toString().c_str());
  pos.tile();
  LOG_DEBUG("Tile : %s\n", pos.toString().c_str());
  return true;
}