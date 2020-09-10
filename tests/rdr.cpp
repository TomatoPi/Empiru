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

/* 
 * File:   rdr.cpp
 * Author: DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 *
 * Created on 10 septembre 2020, 15:08
 */

#include <stdlib.h>
#include <iostream>

#include "gui/utils/Sprite.h"
#include "utils/hex/HexCamera.h"
#include "gui/utils/Window.h"
#include <SDL2/SDL_timer.h>

#include "utils/log.h"
#include "gui/utils/Handler.h"

#define FRAMERATE 60
#define FRAMETIME (1000/FRAMERATE)

#define SIZE 3
#define FACTOR 2

int main(int argc, char** argv) {

  Window *window = Window::createWindow(1920/FACTOR, 1080/FACTOR);
  Sprite *sprite = Sprite::loadFromFile("medias/sol.png", window->renderer);
  HexCamera camera(
    HexCamera::HEXAGON_WIDTH, HexCamera::HEXAGON_HEIGHT,
    window->width, window->height,
    SIZE, SIZE);
  
  Handler handler(&camera, window);
  
  LOG_DEBUG("Window : %d,%d\nSprite : %d,%d\nCamera : %d,%d\n", 
      window->width, window->height,
      sprite->width(), sprite->height(),
      camera.tileWidth(), camera.tileHeight());
  
  camera.target(FlatHexPosition(0,0,FlatHexPosition::Axial));
  
  
  /// \bug Bug d'affichage, les cases sur les bords gauche et haut ne s'affichent pas toujours
  /// Car si la case HautGauche est trop hors de l'ecran
  /// ces cases ne sont pas parcourues lors du rendu

  long tickStartTime, tickEllapsedTime;
  while(handler.handleSDLEvents()) {
    
    tickStartTime = SDL_GetTicks();
    
    camera.update();

    window->clear();
    SDL_Rect rect;
    rect.w = sprite->width();
    rect.h = sprite->height();
    rect.x = 0;
    rect.y = 0;

    FlatHexPosition anchor, pos, off, vx, vy;

    camera.upLeftCorner(&anchor);
    camera.viewPortAxis(&vx, &vy);
//    LOG_DEBUG("Anchor : %s\nVx : %s\n Vy : %s\n", 
//        anchor.toString().c_str(),
//        vx.toString().c_str(),
//        vy.toString().c_str());

    while((rect.y-rect.h) < window->height) {
      pos = anchor;
      rect.x = 0;
      while(rect.x < window->width) {
        camera.tileCenter(pos, &(rect.x), &(rect.y));
        pos.convert(FlatHexPosition::OddQOffset, &off);
        off.tile().convert(FlatHexPosition::OddQOffset);
//        LOG_DEBUG("Anchor : %s\nPOS : %s\nOFF : %s\nRECT : %d,%d\n",
//            anchor.toString().c_str(),
//            pos.toString().c_str(),
//            off.toString().c_str(),
//            rect.x, rect.y);
        if (0 <= off._x && 0 <= off._y && off._x < SIZE && off._y < SIZE) {
//          LOG_WRN("DRAW\n");
          rect.y += 0.5 * camera.tileHeight() - rect.h;
          rect.x -= sprite->width() / 2;
          if (sprite->renderFrame(window->renderer, &rect)) {
            LOG_WRN("%s\n", SDL_GetError());
            OUPS();
          }
        }
        pos = pos + vx;
      }
//      LOG_DEBUG("=========================\n");
      anchor = anchor + vy;
      camera.tileCenter(anchor, &(rect.x), &(rect.y));
    }

    window->update();
    
    tickEllapsedTime = SDL_GetTicks() - tickStartTime;
    if (tickEllapsedTime > FRAMETIME) {
      LOG_WRN("System Overload !! %ld ms late\n", tickEllapsedTime - FRAMETIME);
    }
    else {
      SDL_Delay(FRAMETIME - tickEllapsedTime);
    }
  }
  
  delete sprite;
  delete window;
  
  return EXIT_SUCCESS;
}

