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
#include "utils/gui/Window.h"
#include "controller/events/ControllerEvents.h"
#include "entity/decorators/deposit/Deposit.h"
#include "entity/decorators/storage/Storage.h"
//#include "entity/peon/Peon.h"
//#include "utils/world/Storage.h"
//#include "utils/world/Harvestable.h"
//#include "entity/buildings/site/ConstructSite.h"

namespace {
  /// \brief Array of indexes of ressources icons indexes on icon sheet
  ///   initialized in the ControlPannel constructor
  static std::array<int,Stack::RessourceCount> iconframes;
}

ControlPannel::ControlPannel(
            int viewwidth, int viewheight, 
            Window & window, 
            const TribeInfos & playerTribe) :
  View(0,0,viewwidth, viewheight),
  _window(window),
  _playerTribe(playerTribe),
  _selectedObject(nullptr),
    
  _background(SpriteSheet::loadFromFile(
      "medias/sprites/ui/parts/background.png", 1, 1, window.renderer)), 
  _icons(SpriteSheet::loadFromFile(
      "medias/sprites/ui/parts/icons.png", 1, 4, window.renderer)),
    
  _printer(window.renderer),
  
  _pannel_1{
    int(17 * _window.scale), int(76 * _window.scale), 
    int(128 * _window.scale), 0},
  _pannel_2{
    int(13 * _window.scale), int(230 * _window.scale), 
    int(137 * _window.scale), 0}
{
  /* register icons indexes */
  iconframes[static_cast<std::size_t>(Stack::Ressource::Rock)] = 2;
  iconframes[static_cast<std::size_t>(Stack::Ressource::Wood)] = 3;
  /* register callbacks */
  this->registerEvent<EventObjectSelected>(
      [this](const EventObjectSelected & event) -> void {
        _selectedObject = event._ptr;
      });
  this->registerEvent<EventObjectDeselected>(
      [this](const EventObjectDeselected & event) -> void {
        _selectedObject = nullptr;
      });
}

/// Draw the control pannel
void ControlPannel::draw() {
  /* draw background */
  drawBackround();
  if (_selectedObject) {
    drawObjectInventory(_pannel_1);
  } else {
    drawGlobalRessources(_pannel_1);
  }
  drawControls();
}

void ControlPannel::drawBackround() {
  SDL_Rect rect;
  rect.w = _viewWidth;
  rect.h = _viewHeight;
  rect.x = _offsetX;
  rect.y = _offsetY;
  _background->renderFrame(0, 0, &rect);
}
void ControlPannel::drawGlobalRessources(const SDL_Rect& pannel) {
  SDL_Rect rect;
  rect.w = _icons->width();
  rect.h = _icons->height();
  rect.x = pannel.x;
  rect.y = pannel.y;
  const TribeInfos::TribeStocks & stocks(_playerTribe.stocks());
  for (
      std::size_t type(Stack::RessourceBegin) ; 
      type <= Stack::RessourceEnd ; 
      ++type, rect.y += rect.h + 2)
  {
    _icons->renderFrame(0, iconframes[type], &rect);
    _printer.drawStringAt(rect.x + pannel.w, rect.y + rect.h/2, FontPrinter::CenterRight, 
        std::to_string(stocks[type]));
  }
}
void ControlPannel::drawObjectInventory(const SDL_Rect& pannel) {
  SDL_Rect rect;
  std::vector<std::pair<int,std::string>> inventory;
  const Entity& entity(*_selectedObject);
//  if (Peon *peon = dynamic_cast<Peon*>(&*_selectedObject)) {
//    if (!peon->inventory().empty())
//      inventory.emplace_back(
//        iconframes[peon->inventory().type()], 
//        std::to_string(peon->inventory().size()));
//  }
  if (decorator::Pointer ptr = entity.getDecorator<decorator::Inventory>()) {
    const decorator::Inventory& store(static_cast<const decorator::Inventory&>(*ptr));
    bool depo(nullptr != dynamic_cast<const decorator::Deposit*>(&*ptr));
    for (auto & stack : store.content()) {
      inventory.emplace_back(
        iconframes[static_cast<std::size_t>(stack.type())], 
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
  for (auto & stack : inventory) {
    _icons->renderFrame(0, stack.first, &rect);
    _printer.drawStringAt(
      rect.x + pannel.w, rect.y + rect.h/2, 
      FontPrinter::CenterRight, 
      stack.second);
    rect.y += rect.h + 2;
  }
}
void ControlPannel::drawControls() {
  
}