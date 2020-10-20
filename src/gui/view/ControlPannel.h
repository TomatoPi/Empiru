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

#include "utils/pattern/BigObserver.h"
#include "utils/gui/View.h"
#include "utils/gui/Window.h"
#include "utils/assets/SpriteSheet.h"
#include "utils/gui/FontPrinter.h"
#include "engine/core/entity/EntityPtr.h"

#include "gui/utils/GenericRenderer.h"

#include "engine/tribe/TribeInfos.h"

class ControlPannel : public gui::View, public BigObserver {
private:
  
  Window &           _window;
  const TribeInfos & _playerTribe;
  EntityPtr          _selectedObject;
  
  std::shared_ptr<SpriteSheet> _background; ///< Pannel's background sprite
  std::shared_ptr<SpriteSheet> _icons;      ///< Pannel's icons sprites
  
  FontPrinter   _printer;
  
  SDL_Rect _pannel_1;
  SDL_Rect _pannel_2;
  
public:
  /// Create the control pannel and load right assets
  ControlPannel(
            int viewwidth, int viewheight, 
            Window & window, 
            const TribeInfos & playerTribe);
  
  /// Draw the control pannel
  void draw();
  
private:
  
  void drawBackround();
  void drawGlobalRessources(const SDL_Rect& pannel);
  void drawObjectInventory(const SDL_Rect& pannel);
  void drawGhost();
  void drawControls();
};

#endif /* CONTROLPANNEL_H */
