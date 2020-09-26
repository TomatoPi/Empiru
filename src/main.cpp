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
#include <SDL2/SDL_mixer.h>

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

#include "buildings/House.h"

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
#include "utils/sound/SoundAsset.h"

#include "generator/ZoneGenerator.h"

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
  auto peonMask = SpriteAsset::loadFromFile("medias/peon_palette_animation_mask.png", window->vrenderer);
  
  auto selSprite = SpriteAsset::loadFromFile("medias/peon_palette_animation_select.png", window->renderer);
  auto treeSprite = SpriteAsset::loadFromFile("medias/toufu_tree_palette.png", window->renderer);
  auto treeMask = SpriteAsset::loadFromFile("medias/toufu_tree_palette_mask.png", window->vrenderer);
  
  auto rockSprite = SpriteAsset::loadFromFile("medias/palette_roche_v1.png", window->renderer);
  auto rockMask = SpriteAsset::loadFromFile("medias/palette_roche_v1_mask.png", window->vrenderer);
  
  auto houseSprite = SpriteAsset::loadFromFile("medias/build/house_tower/sprite_house_tower.png", window->renderer);
  auto houseMask = SpriteAsset::loadFromFile("medias/sprite_house_tower_mask.png", window->vrenderer);
  
  
  
  World map(SIZE,SIZE);
  GameEngine game(map);
  
  game.addObjectKind(typeid(Peon), new GenericAllocator<Peon>());
  game.attachBehaviour(typeid(Peon), new PeonBehaviour());
  
  game.addObjectKind(typeid(SelectedPeon), new GenericAllocator<SelectedPeon>());
  game.attachBehaviour(typeid(SelectedPeon), new SelectedPeonBehav());
  
  game.addObjectKind(typeid(Tree), new GenericAllocator<Tree>());
  
  game.addObjectKind(typeid(Rock), new GenericAllocator<Rock>());
  
  game.addObjectKind(typeid(House), new GenericAllocator<House>());
  
  Camera camera(
    hex::Viewport::HEXAGON_WIDTH, hex::Viewport::HEXAGON_HEIGHT,
    window->width, window->height,
    SIZE, SIZE);
  
  GenericRenderer<OnTileBlitter> tilerdr(std::move(groundSprite), nullptr);
  GenericRenderer<OnFootBlitter> treerdr(std::move(treeSprite), std::move(treeMask));
  GenericRenderer<OnFootBlitter> rockrdr(std::move(rockSprite), std::move(rockMask));
  PeonRenderer prdr(std::move(peonSprite), std::move(peonMask));
  SelectedPeonRenderer selrdr(std::move(selSprite));
  GenericRenderer<OnTileBlitter> houserdr(std::move(houseSprite), std::move(houseMask));
  
  camera.target(hex::Axial(0,0));
  
  RenderingEngine rdr(*window, camera, camera, map);
  rdr.attachRenderer(typeid(Tile), tilerdr);
  rdr.attachRenderer(typeid(Peon), prdr);
  rdr.attachRenderer(typeid(SelectedPeon), selrdr);
  rdr.attachRenderer(typeid(Tree), treerdr);
  rdr.attachRenderer(typeid(Rock), rockrdr);
  rdr.attachRenderer(typeid(House), houserdr);
  
  SoundEngine *sounder(SoundEngine::create());
  
  auto selectPeonSound = SoundAsset::loadFromFiles("medias/sounds/peons/peon-", ".ogg", 3);
  
  sounder->registerSound(std::move(selectPeonSound));
  
  Controller controller(map, game, rdr, *sounder);
  SDLHandler handler(camera, camera, controller, rdr, *window);
  
  /* Manualy populate world */
  
  WorldRef *peon(game.createObject(typeid(Peon)));
  (**peon).pos(hex::Axial(0, 0));
  rdr.addTarget(peon);
  map.addObject(peon);
  
  peon = game.createObject(typeid(Peon));
  (**peon).pos(hex::Axial(2, 2));
  rdr.addTarget(peon);
  map.addObject(peon);
  
  WorldRef *tree(game.createObject(typeid(Tree)));
  (**tree).pos(hex::Axial(1, 1));
  rdr.addTarget(tree);
  map.addObject(tree);
  tree = game.createObject(typeid(Tree));
  (**tree).pos(hex::Axial(1.6, 1));
  rdr.addTarget(tree);
  map.addObject(tree);
  tree = game.createObject(typeid(Tree));
  (**tree).pos(hex::Axial(2.6, 1));
  rdr.addTarget(tree);
  map.addObject(tree);
  tree = game.createObject(typeid(Tree));
  (**tree).pos(hex::Axial(1.3, 1.5));
  rdr.addTarget(tree);
  map.addObject(tree);
  
  /* ------------------------------------------------- */
  
  ZoneGenerator zone;
  
  zone.createZone(3);
  zone.addObject();
  
  for (auto obj : zone.objects()){
    LOG_DEBUG("object : %f %f\n",obj._x,obj._y);
    tree = game.createObject(typeid(Tree));
    (**tree).pos(obj);
    prdr.addTarget(tree);
    map.addObject(tree);
  }
  
  for (auto vertex : zone.vertexs()){
    LOG_DEBUG("vertex : %f %f\n",vertex._x,vertex._y);
  }
   
  /* ------------------------------------------------- */
  
  WorldRef *rock(game.createObject(typeid(Rock)));
  (**rock).pos(hex::Axial(0, 2));
  rdr.addTarget(rock);
  map.addObject(rock);
  
  
  WorldRef *house(game.createObject(typeid(House)));
  (**house).pos(hex::Axial(3, 2));
  rdr.addTarget(house);
  map.addObject(house);
  
  /* Main loop */

  long tickStartTime(0), tickEllapsedTime(0);
  double fpsStart(0), avgload(0), avgcount(0), avgfps(0);
  while(true) {
    
    tickStartTime = SDL_GetTicks();
    
    if (!handler.handleSDLEvents()) break;
    
    camera.update();
    game.update();

    window->clear();
    //*
    rdr.render();
    window->update();
    //*/
    /*
    rdr.drawPixelPerfectZones();
    SDL_Surface * screen = SDL_GetWindowSurface(window->window);
    if (!screen) {
      LOG_ERROR("Failed Get Screen : %s\n", SDL_GetError());
      OUPS();
    }
    if (SDL_BlitSurface(window->vsurface, nullptr, screen, nullptr)) {
      LOG_ERROR("%s\n", SDL_GetError());
      OUPS();
    }
    if (SDL_UpdateWindowSurface(window->window)) {
      LOG_ERROR("Failed update window : %s\n", SDL_GetError());
      OUPS();
    }
    //*/
    
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
  //*
  //*/
  
  return 0;
}

