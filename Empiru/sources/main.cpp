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
#include <world/impl/World.h>
#include <game/impl/GEngine.h>
#include <render/impl/REngine.h>
#include <render/impl/PixelPerfectBridge.h>
#include <render/helpers/GenericRTarget.h>
#include <render/helpers/Blitter.h>
#include <render/helpers/AssetLoader.h>
#include <control/impl/CameraCtrl.h>
#include <control/impl/SDLHandler.h>
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
constexpr int WWidth = 1920 / Factor;
constexpr int WHeight = 1080 / Factor;
constexpr int FrameRate = 60;
constexpr int FrameTime = 1000 / FrameRate;
constexpr int SampleTime = 2000;
}

int main(int argc, char **argv) {

  world::impl::World _world(SIZE, SIZE);
  world::IAllocator::registerAllocator(&_world);

  game::impl::GEngine _game;
  game::IDecoAllocator::registerAllocator(&_game);
  game::IOpeAllocator::registerAllocator(&_game);

  auto _window(Window::createWindow(WWidth, WHeight, Factor));
  gui::Viewport _view(0, 0, gui::Viewport::HEXAGON_WIDTH,
      gui::Viewport::HEXAGON_HEIGHT, _window->width, _window->height);

  render::impl::PixelPerfectBridge _bridge(_view, _window->width,
      _window->height);
  render::impl::REngine _rengine(_bridge, _view, _world);
  render::IAllocator::registerAllocator(&_rengine);

  ctrl::impl::CameraCtrl _camera(_window->width, _window->height, _view);
  ctrl::impl::SDLHandler _input(_camera, _bridge);

  {
    using TileTarget = render::helpers::GenericRTarget<render::helpers::OnTileBlitter>;
    TileTarget *tile(new TileTarget(render::ATarget::Pointer(nullptr)));
    TileTarget::Builder builder;
    builder.entity = 0;
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

  _view.target(world::Position(0, 0));

  long tickStartTime(0), tickEllapsedTime(0);
  double fpsStart(0), avgload(0), avgcount(0), avgfps(0);
  while (true) {

    tickStartTime = SDL_GetTicks();

    if (!_input.handleSDLEvents())
      break;

    _camera.update();
//    _gameEngine.update();
//    _playerTribe.update();

    _window->clear();

    _rengine.render();
//    _controlPanel.draw();
    _window->update();

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
