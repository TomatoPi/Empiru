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
/// \file   Window.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 8 septembre 2020, 05:04
///

#include "Window.h"

#include <SDL2/SDL.h>
#include <cassert>
#include <new>

#include "utils/log.h"

Window::Window(
        SDL_Window *window, 
        SDL_Renderer *renderer, 
        int w, int h):
window(window),
renderer(renderer),
width(w),
height(h)
{
}

Window * Window::createWindow(int width, int height) {
  SDL_Window *window;
  SDL_Renderer *renderer;
  /* initialisation de la SDL */
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    LOG_ERROR("Failed Init SDL : %s\n", SDL_GetError());
    return NULL;
  }
  /* creation de la fenetre */
  window = SDL_CreateWindow("Foobar2221", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
  if (!window) {
    LOG_ERROR("Failed Create Window : %s\n", SDL_GetError());
    return NULL;
  }
  /* creation du renderer principal */
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    LOG_ERROR("Failed Create Renderer : %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    return NULL;
  }
  return new Window(window, renderer, width, height);
}
Window::~Window() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
void Window::clear() {
  SDL_SetRenderDrawColor(renderer, 128, 128, 128, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
}
void Window::update() {
  SDL_RenderPresent(renderer);
}
void Window::quitRequest() {
  Window delete();
}