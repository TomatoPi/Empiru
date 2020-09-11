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

#include "gui/utils/Sprite.h"
#include "utils/hex/HexCamera.h"
#include "gui/utils/Window.h"
#include "gui/renderer/WorldRenderer.h"
#include <SDL2/SDL_timer.h>

#include "utils/log.h"
#include "gui/utils/Handler.h"
#include "entity/peon.h"

#define FRAMERATE 60
#define FRAMETIME (1000/FRAMERATE)

#define SIZE 8
#define FACTOR 2

int main(int argc, char** argv) {

  Window *window = Window::createWindow(1920/FACTOR, 1080/FACTOR);
  Sprite *sprite = Sprite::loadFromFile("medias/sol.png", window->renderer);
  //Modif péon <--------------------------------------------------
  Sprite *s_peon = Sprite::loadFromFile("medias/peon.png",window->renderer);
  Peon peon(FlatHexPosition(0,0,FlatHexPosition::Axial));
  //--------------------------------------------------------------
  HexCamera camera(
    HexCamera::HEXAGON_WIDTH, HexCamera::HEXAGON_HEIGHT,
    window->width, window->height,
    SIZE, SIZE, 0);
  
  Handler handler(&camera, window);
  
  
  LOG_DEBUG("Window : %d,%d\nSprite : %d,%d\nCamera : %d,%d\n", 
      window->width, window->height,
      sprite->width(), sprite->height(),
      camera.tileWidth(), camera.tileHeight());
  
  camera.target(FlatHexPosition(0,0,FlatHexPosition::OddQOffset));
  
  WorldRenderer rdr(window, &camera, sprite);
  
  
  /// \bug Bug d'affichage, les cases sur les bords gauche et haut ne s'affichent pas toujours
  /// Car si la case HautGauche est trop hors de l'ecran
  /// ces cases ne sont pas parcourues lors du rendu

  long tickStartTime, tickEllapsedTime;
  while(handler.handleSDLEvents()) {
    
    tickStartTime = SDL_GetTicks();
    
    camera.update();

    window->clear();

    rdr.render();
    
    window->update();
/*
    camera.rotateRight();
    
    rdr.render();
    
    return 0;
//*/
    tickEllapsedTime = SDL_GetTicks() - tickStartTime;
    if (tickEllapsedTime > FRAMETIME) {
      LOG_WRN("System Overload !! %ld ms late\n", tickEllapsedTime - FRAMETIME);
    }
    else {
      SDL_Delay(FRAMETIME - tickEllapsedTime);
    }
  }
  
  delete sprite;
  //Modif péon <--------------------------------------------------
  delete s_peon;
  //--------------------------------------------------------------
  delete window;
  
  return 0;
}

