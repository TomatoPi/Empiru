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
/// \file   ControlPannel.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 27 septembre 2020, 20:04
///
#include "ControlPannel.h"
#include <builtin/items/Ressources.h>
#include <builtin/game/inventory/Inventory.h>
#include <builtin/game/inventory/storage/Storage.h>
#include <builtin/game/inventory/slot/Slot.h>
#include <builtin/game/inventory/deposit/Deposit.h>
#include <control/IGameCtrl.h>
#include <game/IGEngine.h>
#include <map>

namespace {
/// \brief Array of indexes of ressources icons indexes on icon sheet
///   initialized in the ControlPannel constructor
static std::map<items::Ressource::Kind, int> iconframes;
}

namespace gui {

ControlPannel::ControlPannel(int viewwidth, int viewheight, Window &window,
    const tribe::TribeInfos &playerTribe) :
    _window(window), _playerTribe(playerTribe), _selectedInventory(nullptr),

    _background(
        SpriteSheet::loadFromFile("medias/sprites/ui/parts/background.png", 1,
            1, window.renderer)), _icons(
        SpriteSheet::loadFromFile("medias/sprites/ui/parts/icons.png", 1, 4,
            window.renderer)),

    _printer(window.renderer),

    _width(viewwidth), _height(viewheight),

    _pannel_1 { int(17 * _window.scale), int(76 * _window.scale), int(
        128 * _window.scale), 0 },

    _pannel_2 { int(13 * _window.scale), int(230 * _window.scale), int(
        137 * _window.scale), 0 } {
  /* register icons indexes */
  iconframes[items::builtins::ressources::Rock.kind()] =
      2;
  iconframes[items::builtins::ressources::Wood.kind()] =
      3;
  /* register callbacks */
  ctrl::IGameCtrl::Get().ctrl::IGameCtrl::Subject<ctrl::Events::ObjectSelected>::addSubscriber(
      [this](ctrl::IGameCtrl &ctrl,
          ctrl::Events::ObjectSelected &event) -> void {
        _selectedInventory = game::IGEngine::Get().findDecorator(event.uid,
            ::builtin::game::inventory::Inventory::TypeID());
      });
  ctrl::IGameCtrl::Get().ctrl::IGameCtrl::Subject<ctrl::Events::ObjectDeselected>::addSubscriber(
      [this](ctrl::IGameCtrl &ctrl,
          ctrl::Events::ObjectDeselected &event) -> void {
        _selectedInventory = nullptr;
      });
}

/// Draw the control pannel
void ControlPannel::draw() {
  /* draw background */
  drawBackround();
  if (_selectedInventory) {
    drawObjectInventory(_pannel_1);
  } else {
    drawGlobalRessources(_pannel_1);
  }
  drawControls();
}

void ControlPannel::drawBackround() {
  SDL_Rect rect;
  rect.w = _width;
  rect.h = _height;
  rect.x = 0;
  rect.y = 0;
  _background->renderFrame(0, 0, &rect);
}
void ControlPannel::drawGlobalRessources(const SDL_Rect &pannel) {
  SDL_Rect rect;
  rect.w = _icons->width();
  rect.h = _icons->height();
  rect.x = pannel.x;
  rect.y = pannel.y;
  const tribe::TribeInfos::TribeStocks &stocks(_playerTribe.stocks());
  for (auto &stack : stocks) {
    _icons->renderFrame(0, iconframes[stack.type().kind()], &rect);
    _printer.drawStringAt(rect.x + pannel.w, rect.y + rect.h / 2,
        helpers::FontPrinter::CenterRight, std::to_string(stack.size()));
    rect.y += rect.h + 2;
  }
}
void ControlPannel::drawObjectInventory(const SDL_Rect &pannel) {
  SDL_Rect rect;
  std::vector<std::pair<int, std::string>> inventory;
//  if (Peon *peon = dynamic_cast<Peon*>(&*_selectedObject)) {
//    if (!peon->inventory().empty())
//      inventory.emplace_back(
//        iconframes[peon->inventory().type()], 
//        std::to_string(peon->inventory().size()));
//  }
  if (_selectedInventory) {
    bool depo(
        ::builtin::game::inventory::Inventory::Hierarchy().isKindOf(
            ::builtin::game::inventory::Deposit::TypeID(),
            _selectedInventory->kind()));
    for (const items::Stack &stack : _selectedInventory->as<
        ::builtin::game::inventory::Inventory>().content()) {
      inventory.emplace_back(iconframes[stack.type().kind()],
          std::to_string(stack.size())
              + (depo ? "" : "/" + std::to_string(stack.max())));
    }
  }
//  else if (Harvestable *harv = dynamic_cast<Harvestable*>(&*_selectedObject)) {
//  } 
//  else if (
//    ConstructionSite* site = dynamic_cast<ConstructionSite*>(&*_selectedObject))
//  {
//    if (!site->isFilled()) {
//      for (auto & stack : site->recipe()) {
//        inventory.emplace_back(
//            iconframes[stack.first], 
//            std::to_string(site->supplied().at(stack.first))
//              + " "
//              + std::to_string(stack.second));
//      }
//    }
//    else {
//      inventory.emplace_back(0, std::to_string(site->workers().size()));
//      inventory.emplace_back(1, std::to_string(site->progress()));
//    }
//  }
  rect.w = _icons->width();
  rect.h = _icons->height();
  rect.x = pannel.x;
  rect.y = pannel.y;
  for (auto &[frame, str] : inventory) {
    _icons->renderFrame(0, frame, &rect);
    _printer.drawStringAt(rect.x + pannel.w, rect.y + rect.h / 2,
        helpers::FontPrinter::CenterRight, str);
    rect.y += rect.h + 2;
  }
}
void ControlPannel::drawControls() {

}

}  // namespace gui
