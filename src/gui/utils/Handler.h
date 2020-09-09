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


#include <SDL2/SDL.h>
#include "Window.h"

#include "utils/hex/HexCamera.h"


class Handler {
public:
  Handler();
  Handler(const Handler& orig);
  virtual ~Handler();
private:

};

void Handler::EventListenner() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch(event.type) {
    case SDL_QUIT:
      window->quitRequest();
    }
    case SDL_KEYDOWN:
      if (event.key.state == SDL_PRESSED) {
        switch(event.key.keysym.sym) {
          case SDLK_ESCAPE:
            window->quitRequest();
          case SDLK_UP:
            camera->scrollUp();
          case SDLK_DOWN:
            camera->scrollDown();
          case SDLK_RIGHT:
            camera->scrollRight();
          case SDLK_LEFT:
            camera->scrollLeft();
        }
      }
  }
}

void quitRequest() {
  
}

#endif /* HANDLER_H */

