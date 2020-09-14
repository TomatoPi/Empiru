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

#include "gui/Camera.h"
#include "utils/gui/SpriteSheet.h"
#include "utils/gui/Window.h"
#include "gui/RenderingEngine.h"
#include "gui/SmallObjectRenderer.h"
#include "gui/TiledObjectRenderer.h"
#include <SDL2/SDL_timer.h>

#include "utils/log.h"
#include "entity/peon.h"
#include "world/World.h"

#include "controller/SDLHandler.h"
#include "controller/Controller.h"

#define FRAMERATE 60
#define FRAMETIME (1000/FRAMERATE)

#define SIZE 8
#define FACTOR 2

int main(int argc, char** argv) {

  Window *window = Window::createWindow(1920/FACTOR, 1080/FACTOR);
  SpriteSheet *groundSprite = SpriteSheet::loadFromFile("medias/sol.png", 1, window->renderer);
  SpriteSheet *peonSprite = SpriteSheet::loadFromFile("medias/peon.png", 1, window->renderer);
  
  Peon peon(FlatHexPosition(0,0,FlatHexPosition::Axial),FlatHexPosition(0,0,FlatHexPosition::Axial));
  Peon peon2(FlatHexPosition(2,2,FlatHexPosition::Axial),FlatHexPosition(0,0,FlatHexPosition::Axial));
  Peon peon3(FlatHexPosition(-2,2,FlatHexPosition::Axial),FlatHexPosition(0,0,FlatHexPosition::Axial));
  
  World map_test(SIZE,SIZE);
  
  Controller controller(&map_test);
  
  map_test.addObject(&peon);
  map_test.addObject(&peon2);
  map_test.addObject(&peon3);
  LOG_DEBUG("TEST MAP : %s \n",map_test.toString().c_str());
  
  Camera camera(
    HexViewport::HEXAGON_WIDTH, HexViewport::HEXAGON_HEIGHT,
    window->width, window->height,
    SIZE, SIZE);
  
  
  TiledObjectRenderer tilerdr(&camera, groundSprite);
  SmallObjectRenderer prdr(peonSprite);
  
  SDLHandler handler(&camera, &camera, &controller);
  
  
  LOG_DEBUG("Window : %d,%d\nSprite : %d,%d\nCamera : %d,%d\n", 
      window->width, window->height,
      groundSprite->width(), groundSprite->height(),
      camera.tileWidth(), camera.tileHeight());
  
  camera.target(FlatHexPosition(0.5,0,FlatHexPosition::OddQOffset));
  
  RenderingEngine rdr(window, &camera, &map_test, &tilerdr, &prdr);

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
  
  delete groundSprite;
  delete peonSprite;
  delete window;
  
  return 0;
}

