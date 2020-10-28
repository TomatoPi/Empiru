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
#include <window/Window.h>
#include <SDL2/SDL_events.h>

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

namespace {
constexpr std::size_t SIZE = 8;
constexpr float Factor = 1.5;
constexpr int WWidth = 1920 / Factor;
constexpr int WHeight = 1080 / Factor;
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

  bool run(true);
  while (run) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        run = false;
        break;
      }
    }
  }

  return 0;
}
