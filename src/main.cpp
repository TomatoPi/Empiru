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
#include "utils/gui/SpriteAsset.h"
#include "utils/gui/Window.h"
#include "gui/RenderingEngine.h"
#include "gui/SmallObjectRenderer.h"
#include "gui/TiledObjectRenderer.h"
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_mixer.h>

#include "utils/log.h"
#include "entity/Peon.h"
#include "world/World.h"

#include "controller/SDLHandler.h"
#include "controller/Controller.h"
#include "engine/GameEngine.h"

#define FRAMERATE 60
#define FRAMETIME (1000/FRAMERATE)

#define SIZE 8
#define FACTOR 2

int main(int argc, char** argv) {

  Window *window = Window::createWindow(1920/FACTOR, 1080/FACTOR);
  auto groundSprite = SpriteSheet::loadFromFile("medias/sol.png", 1, 1, window->renderer);
  auto peonSprite = SpriteAsset::loadFromFile("medias/peon_palette_animation.png", window->renderer);
  
  Peon peon(FlatHexPosition(0,0,FlatHexPosition::Axial));
  Peon peon2(FlatHexPosition(2,2,FlatHexPosition::Axial));
  
  World map_test(SIZE,SIZE);
  GameEngine gameEngine(&map_test);
  
  Controller controller(&map_test);
  
  gameEngine.addPeon(&peon);
  gameEngine.addPeon(&peon2);
  
  Camera camera(
    HexViewport::HEXAGON_WIDTH, HexViewport::HEXAGON_HEIGHT,
    window->width, window->height,
    SIZE, SIZE);
  
  
  TiledObjectRenderer tilerdr(&camera, std::move(groundSprite));
  SmallObjectRenderer prdr(std::move(peonSprite));
  
  SDLHandler handler(&camera, &camera, &controller);
  
  if (MIX_INIT_OGG != Mix_Init(MIX_INIT_OGG)) {
    LOG_ERROR("Failed start sound engine : %s\n", Mix_GetError());
    OUPS();
  }
  if (0 != Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024)) {
    LOG_ERROR("Failed open audio : %s\n", Mix_GetError());
    OUPS();
  }
  
  camera.target(FlatHexPosition(0.5,0,FlatHexPosition::OddQOffset));
  
  RenderingEngine rdr(window, &camera, &camera, &map_test, &tilerdr, &prdr);

  long tickStartTime, tickEllapsedTime;
  while(true) {
    
    tickStartTime = SDL_GetTicks();
    
    if (!handler.handleSDLEvents()) break;
    
    camera.update();
    gameEngine.update();

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
  
  delete window;
  
  Mix_CloseAudio();
  Mix_Quit();
  
  return 0;
}

