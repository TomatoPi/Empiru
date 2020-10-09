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
/// \brief Utility file for create window and associated renderer
///

#include "Window.h"

#include <SDL2/SDL.h>
#include <cassert>

#include "utils/log.h"

/// \brief Constructor
Window::Window(
          SDL_Window*&& window, SDL_Renderer*&& renderer, 
          SDL_Surface*&& vs, SDL_Renderer*&& vr, 
          int w, int h, float f):
window(window),
renderer(renderer),
    
vsurface(vs),
vrenderer(vr),
    
width(w),
height(h),
scale(f)
{
}

/// \brief Create the window and a renderer
/// \param width : window's width
/// \param height : window's height
/// \return NULL on failure
std::shared_ptr<Window> 
Window::createWindow(int width, int height, float factor) 
{
  /* vars */
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Surface* vsurf;
  SDL_Renderer* vrdr;
  /* initialize SDL */
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    LOG_ERROR("Failed Init SDL : %s\n", SDL_GetError());
    return NULL;
  }
  /* create window */
  window = SDL_CreateWindow("Empiru", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
  if (!window) {
    LOG_ERROR("Failed Create Window : %s\n", SDL_GetError());
    return NULL;
  }
  /* create main renderer */
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    LOG_ERROR("Failed Create Renderer : %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    return NULL;
  }
  /* create virtual surface and software renderer */
  vsurf = SDL_CreateRGBSurface(0, width, height, 32, 0,0,0,0);
  if (!vsurf) {
    LOG_ERROR("Failed Create Surface : %s\n", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return nullptr;
  }
  /* create the software renderer associated with surface */
  vrdr = SDL_CreateSoftwareRenderer(vsurf);
  if (!vrdr) {
    LOG_ERROR("Failed Create Software Renderer : %s\n", SDL_GetError());
    SDL_FreeSurface(vsurf);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return nullptr;
  }
  /* done */
  using std::move;
  return std::make_shared<Window>(
      move(window), move(renderer), 
      move(vsurf), move(vrdr),
      width, height, factor);
}

/// \brief Destructor
Window::~Window() {
  SDL_DestroyRenderer(vrenderer);
  SDL_FreeSurface(vsurface);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

/// \brief Clear the screen
void Window::clear() {
  SDL_SetRenderDrawColor(renderer, 16, 16, 16, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
}

/// \brief Update the screen
void Window::update() {
  SDL_RenderPresent(renderer);
}