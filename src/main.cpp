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

#include <SDL2/SDL_timer.h>
//#include <SDL2/SDL_mixer.h>

#include "gui/Camera.h"
#include "utils/gui/assets/SpriteSheet.h"
#include "utils/gui/assets/SpriteAsset.h"
#include "utils/gui/renderer/GenericRenderer.h"
#include "utils/gui/view/Window.h"
#include "gui/RenderingEngine.h"

#include "entity/peon/Peon.h"
#include "entity/peon/PeonRenderer.h"

#include "entity/tree/Tree.h"

#include "world/World.h"

#include "controller/SDLHandler.h"
#include "controller/Controller.h"

#include "engine/GameEngine.h"

#include "utils/log.h"

#define FRAMERATE 60
#define FRAMETIME (1000/FRAMERATE)
#define AVGFRAME  (2000)

#define SIZE 8
#define FACTOR 2

int main(int argc, char** argv) {

  Window *window = Window::createWindow(1920/FACTOR, 1080/FACTOR);
  auto groundSprite = SpriteAsset::loadFromFile("medias/sol.png", window->renderer);
  auto peonSprite = SpriteAsset::loadFromFile("medias/peonhouette_palette_animation.png", window->renderer);
  auto treeSprite = SpriteAsset::loadFromFile("medias/blue_berry_tree.png", window->renderer);
  
  Peon peon1(FlatHexPosition(0,0,FlatHexPosition::Axial));
  Peon peon2(FlatHexPosition(2,2,FlatHexPosition::Axial));
  
  Tree tree(FlatHexPosition(1, 1, FlatHexPosition::OddQOffset));
  
  World map(SIZE,SIZE);
  GameEngine gameEngine(map);
  
  Controller controller(map);
  
  gameEngine.addPeon(&peon1);
  gameEngine.addPeon(&peon2);
  
  map.addObject(&tree);
  
  Camera camera(
    HexViewport::HEXAGON_WIDTH, HexViewport::HEXAGON_HEIGHT,
    window->width, window->height,
    SIZE, SIZE);
  
  GenericRenderer<OnTileBlitter> tilerdr(std::move(groundSprite));
  GenericRenderer<OnFootBlitter> treerdr(std::move(treeSprite));
  PeonRenderer prdr(std::move(peonSprite));
  
  prdr.addTarget(&peon1);
  prdr.addTarget(&peon2);
  
  SDLHandler handler(camera, camera, controller);
  /*
  if (MIX_INIT_OGG != Mix_Init(MIX_INIT_OGG)) {
    LOG_ERROR("Failed start sound engine : %s\n", Mix_GetError());
    OUPS();
  }
  if (0 != Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024)) {
    LOG_ERROR("Failed open audio : %s\n", Mix_GetError());
    OUPS();
  }
  */
  camera.target(FlatHexPosition(0.5,0,FlatHexPosition::OddQOffset));
  
  RenderingEngine rdr(*window, camera, camera, map);
  rdr.attachRenderer(typeid(Tile), &tilerdr);
  rdr.attachRenderer(typeid(Peon), &prdr);
  rdr.attachRenderer(typeid(Tree), &treerdr);

  long tickStartTime(0), tickEllapsedTime(0);
  double fpsStart(0), avgload(0), avgcount(0), avgfps(0);
  while(true) {
    
    tickStartTime = SDL_GetTicks();
    
    if (!handler.handleSDLEvents()) break;
    
    camera.update();
    gameEngine.update();

    window->clear();
    rdr.render();
    window->update();
    
    ++avgcount;
    avgfps = SDL_GetTicks() - fpsStart;
    if (avgfps >= AVGFRAME) {
      LOG_INFO("AVG FPS  : %3.0f : LOAD : %3.1f%%\n", 
          avgcount * 1000 / avgfps,
          avgload / avgcount);
      fpsStart = SDL_GetTicks();
      avgcount = 0;
      avgload = 0;
    }

    tickEllapsedTime = SDL_GetTicks() - tickStartTime;
    avgload += tickEllapsedTime * 100. / FRAMETIME;
    if (tickEllapsedTime > FRAMETIME) {
      LOG_WRN("System Overload !! %ld ms late\n", tickEllapsedTime - FRAMETIME);
    }
    else {
      SDL_Delay(FRAMETIME - tickEllapsedTime);
    }
  }
  
  delete window;
  /*
  Mix_CloseAudio();
  Mix_Quit();
  */
  return 0;
}

