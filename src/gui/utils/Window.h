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
/// \file   Window.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 8 septembre 2020, 05:04
/// \brief Utility file for create window and associated renderer
///

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

/// \brief Basic window object
class Window {
public:
  
  SDL_Window* window; ///< The window
  SDL_Renderer* renderer; ///< The default renderer

  int width;  ///< Window's width
  int height; ///< Window's height
  
  /// \brief Create the window and a renderer
  /// \param width : window's width
  /// \param height : window's height
  /// \return NULL on failure
  static Window * createWindow(int width, int height);
  /// \brief Destructor
  ~Window();
  
  /// \brief Clear the screen
  void clear();
  /// \brief Update the screen
  void update();
  
private:
  /// \brief Constructor
  Window(SDL_Window *window, SDL_Renderer *renderer, int w, int h);
};

#endif /* WINDOW_H */
