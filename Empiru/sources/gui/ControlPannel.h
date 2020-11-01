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
/// \file   ControlPannel.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 27 septembre 2020, 20:04
///
#ifndef CONTROLPANNEL_H
#define CONTROLPANNEL_H

#include <window/Window.h>
#include <game/Decorator.h>
#include <sprite/SpriteSheet.h>
#include <gui/helpers/FontPrinter.h>
#include <tribe/TribeInfos.h>

namespace gui {

class ControlPannel {
private:

  Window &_window;
  const tribe::TribeInfos &_playerTribe;
  game::Decorator::Pointer _selectedInventory;

  std::shared_ptr<SpriteSheet> _background; ///< Pannel's background sprite
  std::shared_ptr<SpriteSheet> _icons;      ///< Pannel's icons sprites

  helpers::FontPrinter _printer;

  int _width;
  int _height;

  SDL_Rect _pannel_1;
  SDL_Rect _pannel_2;

public:
  /// Create the control pannel and load right assets
  ControlPannel(int viewwidth, int viewheight, Window &window,
      const tribe::TribeInfos &playerTribe);

  /// Draw the control pannel
  void draw();

private:

  void drawBackround();
  void drawGlobalRessources(const SDL_Rect &pannel);
  void drawObjectInventory(const SDL_Rect &pannel);
  void drawGhost();
  void drawControls();
};

}  // namespace gui

#endif /* CONTROLPANNEL_H */
