/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: tomato
 *
 * Created on 6 septembre 2020, 17:18
 */

#include <cstdlib>
#include <SDL2/SDL.h>

#include "gui/utils/Sprite.h"
#include "utils/hex/HexCamera.h"
#include "gui/utils/Window.h"

#include "utils/log.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
  
  Window *window = Window::createWindow(1920/2, 1080/2);
  Sprite *sprite = Sprite::loadFromFile("medias/sol.png", window->renderer);
  HexCamera camera(sprite->width(), HexCamera::vfactor);
  
  LOG_DEBUG("Window : %d,%d\nSprite : %d,%d\nCamera : %f,%f\n", 
      window->width, window->height,
      sprite->width(), sprite->height(),
      camera.tileWidth(), camera.tileHeight());

  window->clear();
  SDL_Rect rect;
  rect.w = sprite->width();
  rect.h = sprite->height();
  
  for (int x = 0 ; x < window->width ; x += sprite->width()) {
    for (int y = 0 ; y < window->height ; y += camera.tileHeight()) {
      rect.x = x;
      rect.y = y;
      if (sprite->renderFrame(window->renderer, &rect)) {
        LOG_WRN("%s\n", SDL_GetError());
        OUPS();
      }
    }
  }
  
  window->update();
  
  SDL_Delay(3000);
  
  return 0;
}

