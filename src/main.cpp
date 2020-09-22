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

#include "entity/rock/Rock.h"

#include "world/World.h"

#include "controller/SDLHandler.h"
#include "controller/Controller.h"
#include "controller/selection/SelectedPeon.h"
#include "controller/selection/SelectedPeonBehaviour.h"
#include "controller/selection/SelectedPeonRenderer.h"

#include "engine/GenericAllocator.h"
#include "engine/GameEngine.h"

#include "utils/log.h"
#include "entity/peon/PeonBehaviour.h"

#define FRAMERATE 60                ///< Target FPS
#define FRAMETIME (1000/FRAMERATE)  ///< Duration of a frame (ms)
#define AVGFRAME  (2000)            ///< Interval between FPS prompt (ms)

#define SIZE 8    ///< World size (square world)
#define FACTOR 2  ///< Magic number scalling window size

/// \brief Too complex to explain what is this thing
int main(int argc, char** argv) {

  Window *window = Window::createWindow(1920/FACTOR, 1080/FACTOR);
  auto groundSprite = SpriteAsset::loadFromFile("medias/sol.png", window->renderer);
  auto peonSprite = SpriteAsset::loadFromFile("medias/peon_palette_animation.png", window->renderer);
  auto selSprite = SpriteAsset::loadFromFile("medias/peon_palette_animation_select.png", window->renderer);
  auto treeSprite = SpriteAsset::loadFromFile("medias/toufu_tree_palette.png", window->renderer);
  auto rockSprite = SpriteAsset::loadFromFile("medias/palette_roche_v1.png", window->renderer);
  
  World map(SIZE,SIZE);
  GameEngine game(map);
  
  game.addObjectKind(typeid(Peon), new GenericAllocator<Peon>());
  game.attachBehaviour(typeid(Peon), new PeonBehaviour());
  
  game.addObjectKind(typeid(SelectedPeon), new GenericAllocator<SelectedPeon>());
  game.attachBehaviour(typeid(SelectedPeon), new SelectedPeonBehav());
  
  game.addObjectKind(typeid(Tree), new GenericAllocator<Tree>());
  
  game.addObjectKind(typeid(Rock), new GenericAllocator<Rock>());
  
  Camera camera(
    HexViewport::HEXAGON_WIDTH, HexViewport::HEXAGON_HEIGHT,
    window->width, window->height,
    SIZE, SIZE);
  
  GenericRenderer<OnTileBlitter> tilerdr(std::move(groundSprite));
  GenericRenderer<OnFootBlitter> treerdr(std::move(treeSprite), 0, 5);
  GenericRenderer<OnFootBlitter> rockrdr(std::move(rockSprite));
  PeonRenderer prdr(std::move(peonSprite));
  SelectedPeonRenderer selrdr(std::move(selSprite));
  
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
  rdr.attachRenderer(typeid(Tile), tilerdr);
  rdr.attachRenderer(typeid(Peon), prdr);
  rdr.attachRenderer(typeid(SelectedPeon), selrdr);
  rdr.attachRenderer(typeid(Tree), treerdr);
  rdr.attachRenderer(typeid(Rock), rockrdr);
  
  Controller controller(map, game, rdr);
  SDLHandler handler(camera, camera, controller);
  
  /* Manualy populate world */
  
  WorldRef *peon(game.createObject(typeid(Peon)));
  (**peon).pos(FlatHexPosition(0, 0, FlatHexPosition::Axial));
  rdr.addTarget(peon);
  map.addObject(peon);
  
  peon = game.createObject(typeid(Peon));
  (**peon).pos(FlatHexPosition(2, 2, FlatHexPosition::Axial));
  rdr.addTarget(peon);
  map.addObject(peon);
  
  WorldRef *tree(game.createObject(typeid(Tree)));
  (**tree).pos(FlatHexPosition(1, 1, FlatHexPosition::Axial));
  rdr.addTarget(tree);
  map.addObject(tree);
  tree = game.createObject(typeid(Tree));
  (**tree).pos(FlatHexPosition(1.6, 1, FlatHexPosition::Axial));
  rdr.addTarget(tree);
  map.addObject(tree);
  tree = game.createObject(typeid(Tree));
  (**tree).pos(FlatHexPosition(2.6, 1, FlatHexPosition::Axial));
  rdr.addTarget(tree);
  map.addObject(tree);
  tree = game.createObject(typeid(Tree));
  (**tree).pos(FlatHexPosition(1.3, 1.5, FlatHexPosition::Axial));
  rdr.addTarget(tree);
  map.addObject(tree);
  
  WorldRef *rock(game.createObject(typeid(Rock)));
  (**rock).pos(FlatHexPosition(0, 2, FlatHexPosition::Axial));
  rdr.addTarget(rock);
  map.addObject(rock);
  
  /* Main loop */

  long tickStartTime(0), tickEllapsedTime(0);
  double fpsStart(0), avgload(0), avgcount(0), avgfps(0);
  while(true) {
    
    tickStartTime = SDL_GetTicks();
    
    if (!handler.handleSDLEvents()) break;
    
    camera.update();
    game.update();

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

