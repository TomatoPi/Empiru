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
/// \date 27 oct. 2020 01:15:20
///
#include <builtin/items/Ressources.h>
#include <builtin/game/deposit/DepositE.h>
#include <builtin/game/inventory/Inventory.h>
#include <builtin/game/inventory/deposit/Deposit.h>
#include <builtin/game/inventory/slot/Slot.h>
#include <builtin/game/inventory/storage/Storage.h>

#include <alloc/helpers/logger.h>
#include <world/impl/World.h>
#include <world/generator/ZoneGenerator.h>
#include <game/impl/GEngine.h>
#include <render/impl/REngine.h>
#include <render/impl/PixelPerfectBridge.h>
#include <render/helpers/GenericRTarget.h>
#include <render/helpers/Blitter.h>
#include <render/helpers/AssetLoader.h>
#include <control/impl/CameraCtrl.h>
#include <control/impl/SDLHandler.h>
#include <control/impl/Controller.h>
#include <control/helpers/GenericECtrls.h>
#include <gui/ControlPannel.h>
#include <window/Window.h>
#include <SDL2/SDL_timer.h>
#include <log/log.h>

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

namespace {
constexpr std::size_t SIZE = 8;
constexpr float Factor = 1.5;
constexpr int PWidth = 409 /Factor;
constexpr int WWidth = 1920 / Factor;
constexpr int WHeight = 1080 / Factor;
constexpr int FrameRate = 60;
constexpr int FrameTime = 1000 / FrameRate;
constexpr int SampleTime = 2000;

template<typename T>
using AAllocator = alloc::IndexAllocator<T, render::ATarget>;
template<typename T>
using DAllocator = alloc::IndexAllocator<T, game::Decorator>;
template<typename T>
using OAllocator = alloc::IndexAllocator<T, game::Operator>;
}

int main(int argc, char **argv) {

  LOG::LogLevel = LOG::Level::Debug;

  world::impl::World _world(SIZE, SIZE);
  world::IAllocator::registerAllocator(&_world);
  world::IMap::registerMap(&_world);

  game::impl::GEngine _game;
  game::IDecoAllocator::registerAllocator(&_game);
  game::IOpeAllocator::registerAllocator(&_game);
  game::IGEngine::registerGEngine(&_game);

  auto _window(Window::createWindow(WWidth, WHeight, Factor));
  gui::Viewport _view(PWidth, 0, gui::Viewport::HEXAGON_WIDTH,
      gui::Viewport::HEXAGON_HEIGHT, _window->width, _window->height);

  render::impl::PixelPerfectBridge _bridge(_view, _window->width,
      _window->height);
  render::impl::REngine _rengine(_bridge, _view, _world);
  render::IAllocator::registerAllocator(&_rengine);
  render::IREngine::registerREngine(&_rengine);

  ctrl::impl::CameraCtrl _camera(_window->width, _window->height, _view);
  ctrl::impl::SDLHandler _input(_camera, _bridge);
  ctrl::impl::Controller _controller;
  ctrl::IGameCtrl::registerController(&_controller);

  {
    using TileTarget = render::helpers::GenericRTarget<render::helpers::OnTileBlitter>;
    TileTarget *tile(new TileTarget(render::ATarget::Pointer(nullptr)));
    TileTarget::Builder builder;
    builder.entity = game::EUID();
    builder.kind = 0;
    builder.asset = render::helpers::loadAsset("medias/sprites/land/tile/tile",
        render::helpers::Sheet::ReqSheet, _window->renderer,
        _bridge.renderer());
    builder.pos = world::Position();
    builder.ori = 0;
    builder.blitter = render::helpers::OnTileBlitter();
    builder(*tile);
    _rengine.setTileTarget(tile);
  }
  game::EUID tree;
  {
    /* register tree ressource */
    items::Ressource::Kind _TreeRessource = items::builtins::ressources::Wood.kind();
    game::EUID::Kind _TreeKind = game::EUID::Hierarchy().newKind();
    /* register tree asset */
    using DepositTarget = render::helpers::GenericRTarget<render::helpers::OnFootBlitter>;
    render::AssetUID _TreeAsset = _rengine.registerAsset( // @suppress("Invalid arguments")
        render::helpers::loadAsset("medias/sprites/land/tree/toufu",
            render::helpers::Sheet::ReqSheet | render::helpers::Sheet::ReqMask,
            _window->renderer, _bridge.renderer()),
        new alloc::helpers::LoggerDecorator(new AAllocator<DepositTarget>()));
    /* register deposit decorator */
    using DepositInventory = builtin::game::inventory::Deposit;
    _game.registerDecorator(builtin::game::inventory::Inventory::TypeID(),
        nullptr);
    _game.registerDecorator( // @suppress("Invalid arguments")
        DepositInventory::TypeID(),
        new alloc::helpers::LoggerDecorator(
            new DAllocator<DepositInventory>()));
    _game.registerDecorator( // @suppress("Invalid arguments")
        builtin::game::inventory::Slot::TypeID(),
        new alloc::helpers::LoggerDecorator(
            new DAllocator<builtin::game::inventory::Slot>()));
    _game.registerDecorator( // @suppress("Invalid arguments")
        builtin::game::inventory::Storage::TypeID(),
        new alloc::helpers::LoggerDecorator(
            new DAllocator<builtin::game::inventory::Storage>()));
    /* add a controller for trees */
    _controller.registerEntityController(_TreeKind, new ctrl::helpers::GenericEntityController());
    /* build a tree */
    DepositTarget::Builder tbuilder;
    tbuilder.kind = _TreeAsset;
    tbuilder.blitter = render::helpers::OnFootBlitter();
    /* entity basics */
    builtin::game::deposit::Builder ebuilder;
    ebuilder.kind = _TreeKind;
    ebuilder.size = world::Object::Size::Small;
    ebuilder.pos = world::Position();
    ebuilder.orientation = 0;
    ebuilder.tbuilder = &tbuilder;
    /* deposit things */
    ebuilder.type = _TreeRessource;
    ebuilder.difficulty = 5;
    ebuilder.qty = 100;
    /* let's build a great w... tree */
    tree = _game.createEntity(ebuilder);
  }

  tribe::TribeInfos _tribe;

  gui::ControlPannel _pannel(PWidth, WHeight, *_window, _tribe);

  {
    ZoneGenerator generator;
    generator.createZone(3);
    generator.addObject();
  }

  _view.target(world::Position(0, 0));

  long tickStartTime(0), tickEllapsedTime(0);
  double fpsStart(0), avgload(0), avgcount(0), avgfps(0);
  while (true) {

    tickStartTime = SDL_GetTicks();

    if (!_input.handleSDLEvents())
      break;

    _camera.update();
    _game.update();

    _window->clear();

    _rengine.render();
    _pannel.draw();
    _window->update();

    _game.destroyGarbadge();
    _world.destroyGarbage();
    _rengine.destroyGarbadge();

    ++avgcount;
    avgfps = SDL_GetTicks() - fpsStart;
    if (avgfps >= SampleTime) {
      LOG::info("AVG FPS :", std::setprecision(3), std::setw(3),
          avgcount * 1000 / avgfps, ": LOAD :", avgload / avgcount, "%");
      fpsStart = SDL_GetTicks();
      avgcount = 0;
      avgload = 0;
    }

    tickEllapsedTime = SDL_GetTicks() - tickStartTime;
    avgload += tickEllapsedTime * 100. / FrameTime;
    if (tickEllapsedTime < FrameTime) {
      SDL_Delay(FrameTime - tickEllapsedTime);
    }
  }

  return 0;
}
