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

#include "utils/log.h"

#include "utils/alloc/IndexAllocator.h"

#include "engine/core/entity/Entity.h"
#include "engine/core/decorator/Decorator.h"
#include "engine/impl/GameEngine.h"

#include "world/impl/WorldMap.h"

#include "controller/impl/Controller.h"
#include "controller/impl/SDLHandler.h"
#include "controller/utils/GenericSelectorController.h"

#include "gui/impl/Camera.h"
#include "gui/impl/RenderingEngine.h"

#include "sound/SoundEngine.h"

#include "entity/peon/PeonEntity.h"
#include "entity/peon/PeonRenderer.h"
#include "entity/peon/PeonController.h"

#include "entity/land/tree/Tree.h"
#include "entity/land/rock/Rock.h"

#include "entity/buildings/house/House.h"

#include "entity/utils/deposit/DepositEntityBeh.h"

#include "entity/decorators/mover/Mover.h"
#include "entity/decorators/mover/MoverBeh.h"

#include "entity/decorators/deposit/Deposit.h"
#include "entity/decorators/storage/Storage.h"
#include "engine/tribe/TribeInfos.h"
#include "entity/decorators/slot/Slot.h"
#include "entity/decorators/collector/Collector.h"
#include "entity/decorators/worker/WorkerBeh.h"

#define FRAMERATE 60                ///< Target FPS
#define FRAMETIME (1000/FRAMERATE)  ///< Duration of a frame (ms)
#define AVGFRAME  (2000)            ///< Interval between FPS prompt (ms)

#define SIZE 8    ///< World size (square world)
#define FACTOR 1.5  ///< Magic number scalling window size

namespace {
  template <class T>
  using EntityAllocator = alloc::IndexAllocator<T,Entity>;
  template <class T>
  using DecoratorAllocator = alloc::IndexAllocator<T,deco::Decorator>;
}

/// \brief Too complex to explain what is this thing
int main(int argc, char** argv) {
  
  /* Create the World and main engine */
  Controller _gameController;
  WorldMap   _worldMap(SIZE,SIZE);
  GameEngine _gameEngine(_worldMap);
  TribeInfos _playerTribe;
  
  /* Create the UI */
  std::shared_ptr<Window> _window = 
    Window::createWindow(1920/FACTOR, 1080/FACTOR, FACTOR);
  ControlPannel _controlPanel(
    409/FACTOR, 1080/FACTOR, 
    *_window.get(), 
    _playerTribe);
  Camera _camera(
    371/FACTOR, 0,
    hex::Viewport::HEXAGON_WIDTH, hex::Viewport::HEXAGON_HEIGHT,
    _window->width, _window->height,
    SIZE, SIZE);
  RenderingEngine _rdrEngine(*_window.get(), _camera, _camera, _worldMap);
  SDLHandler _sdlHandler(_camera, _camera, _gameController, _controlPanel, _rdrEngine);
  
  /* Create the sound Engine */
  SoundEngine *_soundEngine(SoundEngine::create());
  
  /* Create the assets managers */
  gui::TypedRegister& _spritesRegister(gui::TypedRegister::Get());
  
  /* Setup things and Attach the Engines together */
  _camera.target(hex::Axial(0,0));
  
  _gameController.attachObserver(&_rdrEngine);
  _gameController.attachObserver(_soundEngine);
  _gameController.attachObserver(&_controlPanel);
  
  _gameEngine.attachObserver(&_rdrEngine);
  _gameEngine.attachObserver(&_gameController);
  _gameEngine.attachObserver(&_playerTribe);
  
  /* Register basic kinds */
  
  {
    _gameEngine.registerDecorator(typeid(deco::Mover), 
        new DecoratorAllocator<deco::Mover>(), 
        new deco::MoverBeh(_worldMap));
    _gameEngine.registerDecorator(typeid(deco::Deposit),
        new DecoratorAllocator<deco::Deposit>(),
        nullptr);
    _gameEngine.registerDecorator(typeid(deco::Storage),
        new DecoratorAllocator<deco::Storage>(),
        nullptr);
    _gameEngine.registerDecorator(typeid(deco::Slot),
        new DecoratorAllocator<deco::Slot>(),
        nullptr);
    _gameEngine.registerDecorator(typeid(deco::Collector),
        new DecoratorAllocator<deco::Collector>(),
        new deco::WorkerBeh());
  }
  
  { /* tile */
    auto asset(_spritesRegister.registerAsset(typeid(Tile),
        "medias/sprites/land/ground_super", 
        gui::ObjectAsset::ReqSheet, 
        _window->renderer,
        _window->vrenderer));
    
    _rdrEngine.attachRenderer(typeid(Tile), 
        new GenericRenderer<OnTileBlitter>(asset));
  }
  { /* peon */
    PeonRenderer::SheetsPaths paths;
    paths.whareh_sheet = "medias/sprites/entity/peon/attached_warehouse.png";
    paths.notify_sheet = "medias/sprites/entity/peon/notify.png";
    
    auto asset(_spritesRegister.registerAsset(typeid(Peon),
        "medias/sprites/entity/peon/peon", 
        gui::ObjectAsset::ReqSheet
          | gui::ObjectAsset::ReqMask
          | gui::ObjectAsset::ReqSelect, 
        _window->renderer,
        _window->vrenderer));
    
    _gameEngine.registerEntity(typeid(Peon), new EntityAllocator<Peon>(), nullptr);
    _rdrEngine.attachRenderer(typeid(Peon), 
        new PeonRenderer(asset, paths, _window->renderer));
    _soundEngine->registerSound(SoundAsset::loadFromFiles(
        "medias/sounds/peons/peon-", ".ogg", 3));
    _gameController.registerController(typeid(Peon), 
        new PeonController(_gameController));
  }
  { /* Tree */
    auto asset(_spritesRegister.registerAsset(typeid(Tree),
        "medias/sprites/land/toufu", 
        gui::ObjectAsset::ReqSheet | gui::ObjectAsset::ReqMask, 
        _window->renderer,
        _window->vrenderer));
    
    _gameEngine.registerEntity(typeid(Tree), 
        new EntityAllocator<Tree>(), 
        new DepositEntityBeh(_gameEngine));
    _rdrEngine.attachRenderer(typeid(Tree), 
        new GenericRenderer<OnFootBlitter>(asset));
    _gameController.registerController(typeid(Tree), 
        new GenericSelectorController(_gameController));
  }
  { /* Rocks */
    auto asset(_spritesRegister.registerAsset(typeid(Rock),
        "medias/sprites/land/rock", 
        gui::ObjectAsset::ReqSheet | gui::ObjectAsset::ReqMask, 
        _window->renderer,
        _window->vrenderer));
    
    _gameEngine.registerEntity(typeid(Rock), 
        new EntityAllocator<Rock>(), 
        new DepositEntityBeh(_gameEngine));
    _rdrEngine.attachRenderer(typeid(Rock), 
        new GenericRenderer<OnFootBlitter>(asset));
    _gameController.registerController(typeid(Rock), 
        new GenericSelectorController(_gameController));
  }
  { /* House */
    auto asset(_spritesRegister.registerAsset(typeid(House),
        "medias/sprites/buildings/house_peon/house_peon", 
        gui::ObjectAsset::ReqSheet 
          | gui::ObjectAsset::ReqMask 
          | gui::ObjectAsset::ReqGhost, 
        _window->renderer,
        _window->vrenderer));
    
    _gameEngine.registerEntity(typeid(House), 
        new EntityAllocator<House>(),
        nullptr);
    _rdrEngine.attachRenderer(typeid(House), 
        new GenericRenderer<OnTileBlitter>(asset));
    _gameController.registerController(typeid(House), 
        new GenericSelectorController(_gameController));
  }
#if 0
  { /* Warehouse */
    auto asset(_spritesRegister.registerAsset(typeid(Warehouse),
        "medias/sprites/buildings/house_tower/house", 
        gui::ObjectAsset::ReqSheet 
          | gui::ObjectAsset::ReqMask 
          | gui::ObjectAsset::ReqGhost, 
        _window->renderer,
        _window->vrenderer));
    
    _gameEngine.registerObjectKind(typeid(Warehouse), new WorldAllocator<Warehouse>());
    _gameEngine.attachBehaviour(typeid(Warehouse), 
        new StorageBehaviour(_gameEngine.playerTribe()));
    _rdrEngine.attachRenderer(typeid(Warehouse), 
        new GenericRenderer<OnTileBlitter>(asset));
  }
  { /* ghost */
    _gameEngine.registerObjectKind(typeid(ConstructionGhost), 
        new WorldAllocator<ConstructionGhost>());
    _rdrEngine.attachRenderer(typeid(ConstructionGhost), new GhostRenderer());
  }
  { /* site */
    auto asset(_spritesRegister.registerAsset(typeid(ConstructionSite),
        "medias/sprites/buildings/site/site", 
        gui::ObjectAsset::ReqSheet 
          | gui::ObjectAsset::ReqMask, 
        _window->renderer,
        _window->vrenderer));
    
    _gameEngine.registerObjectKind(typeid(ConstructionSite), 
        new WorldAllocator<ConstructionSite>());
    _gameEngine.attachBehaviour(typeid(ConstructionSite), new SiteBehaviour());
    _rdrEngine.attachRenderer(typeid(ConstructionSite), 
        new SiteRenderer(asset));
  }
#endif
  
  /* Manualy populate world */
  
  _gameEngine.createEntity(typeid(Peon), 
      Peon::Builder(_gameEngine, WorldObject::Position(0,0)));
  _gameEngine.createEntity(typeid(Peon), 
      Peon::Builder(_gameEngine, WorldObject::Position(2,2)));
  
  _gameEngine.createEntity(typeid(Tree), 
      Tree::Builder(_gameEngine, WorldObject::Position(1,1)));
  _gameEngine.createEntity(typeid(Tree), 
      Tree::Builder(_gameEngine, WorldObject::Position(1.6,1)));
  _gameEngine.createEntity(typeid(Tree), 
      Tree::Builder(_gameEngine, WorldObject::Position(2.6,1)));
  _gameEngine.createEntity(typeid(Tree), 
      Tree::Builder(_gameEngine, WorldObject::Position(1.3,1.5)));
  
  _gameEngine.createEntity(typeid(Rock), 
      Rock::Builder(_gameEngine, WorldObject::Position(0,2)));
  
  _gameEngine.createEntity(typeid(House), 
      House::Builder(_gameEngine, WorldObject::Position(3,2)));
 
  /* ------------------------------------------------- */
  
//  ZoneGenerator zone;
//  
//  zone.createZone(3);
//  zone.addObject();
//  
//  for (auto obj : zone.objects()) {
//    LOG_DEBUG("object : %f %f\n",obj._x,obj._y);
//    _gameEngine.createObject(typeid(Tree), MoverTo(obj._x, obj._y));
//  }
//  
//  for (auto vertex : zone.vertexs()) {
//    LOG_DEBUG("vertex : %f %f\n",vertex._x,vertex._y);
//  }
   
  /* ------------------------------------------------- */
  
  /* Main loop */

  long tickStartTime(0), tickEllapsedTime(0);
  double fpsStart(0), avgload(0), avgcount(0), avgfps(0);
  while(true) {
    
    tickStartTime = SDL_GetTicks();
    
    if (!_sdlHandler.handleSDLEvents()) break;
    
    _camera.update();
    _gameEngine.update();
    _playerTribe.update();
    
    _window->clear();
    
    _rdrEngine.render();
    _controlPanel.draw();
    _window->update();
    
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
  
  return 0;
}

