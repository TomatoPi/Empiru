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
/// \file   main.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 6 septembre 2020, 17:18
///

#include <cstdlib>

#include "gui/utils/Sprite.h"
#include "gui/impl/Camera.h"
#include "gui/utils/Window.h"
#include "gui/renderer/WorldRenderer.h"
#include <SDL2/SDL_timer.h>

#include "utils/log.h"
#include "gui/utils/Handler.h"
#include "entity/peon.h"
#include "world/utils/World.h"
#include "engine/controller.h"

#define FRAMERATE 60
#define FRAMETIME (1000/FRAMERATE)

#define SIZE 8
#define FACTOR 2

int main(int argc, char** argv) {

  Window *window = Window::createWindow(1920/FACTOR, 1080/FACTOR);
  Sprite *sprite = Sprite::loadFromFile("medias/sol.png", window->renderer);
  PeonRenderer *prdr = PeonRenderer::create("medias/peon.png",window->renderer);
  
  Peon peon(FlatHexPosition(0,0,FlatHexPosition::Axial));
  Peon peon2(FlatHexPosition(2,2,FlatHexPosition::Axial));
  Peon peon3(FlatHexPosition(-2,2,FlatHexPosition::Axial));
  Controller controller;
  World map_test(SIZE,SIZE);
  
  map_test.addObject(&peon);
  map_test.addObject(&peon2);
  map_test.addObject(&peon3);
  LOG_DEBUG("TEST MAP : %s \n",map_test.toString().c_str());
  
  Camera camera(
    HexViewport::HEXAGON_WIDTH, HexViewport::HEXAGON_HEIGHT,
    window->width, window->height,
    SIZE, SIZE);
  
  Handler handler(&camera, window, &map_test, &controller);
  
  
  LOG_DEBUG("Window : %d,%d\nSprite : %d,%d\nCamera : %d,%d\n", 
      window->width, window->height,
      sprite->width(), sprite->height(),
      camera.tileWidth(), camera.tileHeight());
  
  camera.target(FlatHexPosition(0.5,0,FlatHexPosition::OddQOffset));
  
  WorldRenderer rdr(window, &camera, sprite, &map_test, prdr);

  long tickStartTime, tickEllapsedTime;
  while(handler.handleSDLEvents()) {
    
    tickStartTime = SDL_GetTicks();
    
    camera.update();

    window->clear();

    rdr.render();
    
    window->update();

    tickEllapsedTime = SDL_GetTicks() - tickStartTime;
    if (tickEllapsedTime > FRAMETIME) {
      LOG_WRN("System Overload !! %ld ms late\n", tickEllapsedTime - FRAMETIME);
    }
    else {
      SDL_Delay(FRAMETIME - tickEllapsedTime);
    }
  }
  
  delete sprite;
  delete prdr;
  delete window;
  
  return 0;
}

