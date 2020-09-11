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

#define MERGE 50

Handler::Handler(HexCamera *c, Window *w, World *world, Controller *controller) :
  _camera(c),
  _window(w),
  _world(world),
  _controller(controller)
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
    case SDLK_a:
      _camera->rotateLeft();
      LOG_DEBUG("camera n° : %d \n", _camera->getOrientation());
      break;
    case SDLK_e:
      _camera->rotateRight();
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

bool Handler::handleMouseButtonDown(const SDL_MouseButtonEvent & event){
  FlatHexPosition pos;
  
  _camera->fromPixel(event.x, event.y, &pos);
  pos.convert(FlatHexPosition::Grid);
  
  switch(event.button){
    case SDL_BUTTON_LEFT:
      handleMouseButtonLeftDown(pos);
      break;
    case SDL_BUTTON_RIGHT:
      handleMouseButtonRightDown(pos);
      break;
  }
  
  return true;
}

bool Handler::handleMouseButtonLeftDown(const FlatHexPosition & pos) {
  auto tmp_world = _world->getVectorFromPos(pos);
  
  if (tmp_world != nullptr){
    for (auto peon : *tmp_world){
      LOG_DEBUG("PEON : %f %f %f\n",peon->pos()._x,
            peon->pos()._y,
            peon->pos()._z);
      FlatHexPosition tmp_pos(peon->pos(),FlatHexPosition::Grid);
      if (((pos._x >= tmp_pos._x) && (pos._y >= tmp_pos._y)) 
          && ((pos._x < tmp_pos._x + 1) && (pos._y < tmp_pos._y + 0.5))){
        
        LOG_DEBUG("IF -----> ET MA HACHE : %f %f %f\n",peon->pos()._x,
            peon->pos()._y,
            peon->pos()._z);
        _controller->selectPeon(peon);
        LOG_DEBUG("Peon has been selected ! \n");
      }
      else {
        LOG_DEBUG("Peon has been deselected\n");
        _controller->selectPeon(nullptr);
      }
     }
  }
  
  else {
    LOG_DEBUG("Peon has been deselected\n");
    _controller->selectPeon(nullptr);
  }
  
  return true;
}


bool Handler::handleMouseButtonRightDown(const FlatHexPosition & pos){
  LOG_DEBUG("MDR CA MARCHEEEEEEEEEEEEEEE\n");
  return true;
}