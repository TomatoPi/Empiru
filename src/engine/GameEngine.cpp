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
/// \file   Engine.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 12 septembre 2020, 08:51
///

#include "GameEngine.h"

#include "utils/log.h"
#include <cmath>

/// \brief Constructor
GameEngine::GameEngine(World *w, ControllerState *c) :
  _world(w), _controller(c)
{
  
}
  
/// \brief Called when a left click is performed at given position
void GameEngine::leftClickAt(const FlatHexPosition & click) {
  
  LOG_DEBUG("Search at : %s\n%s\n", click.toString().c_str(), _world->toString().c_str());
  auto tmp_world = _world->getVectorFromPos(click);
  
  //LOG_DEBUG("%s\n", _world->toString().c_str());
  
  if (tmp_world != nullptr){
    for (auto peon : *tmp_world){
      LOG_DEBUG("PEON pos : %s target : %s\n",peon->pos().toString().c_str(),peon->targetPos().toString().c_str());
      FlatHexPosition tmp_pos(peon->pos(),FlatHexPosition::Grid);
      LOG_DEBUG("CLIC : %s\n", click.toString().c_str());
      LOG_DEBUG("pos : %s tmp_pos : %s \n",click.toString().c_str(),tmp_pos.toString().c_str());
      if ((fabs(click._x - tmp_pos._x) < 0.25) && (fabs(click._y + 0.25 - tmp_pos._y) < 0.25)) {
        
        LOG_DEBUG("IF -----> ET MA HACHE : %f %f %f\n",peon->pos()._x,
            peon->pos()._y,
            peon->pos()._z);
        _controller->selectPeon(peon);
        LOG_DEBUG("Peon has been selected ! \n");
      } else {
        LOG_DEBUG("Peon has been deselected\n");
        _controller->deselectPeon();
      }
     }
  } else {
    LOG_DEBUG("Péonhouète\n");
    _controller->deselectPeon();
  }
}
/// \brief Called when a right click is performed at given position
void GameEngine::rightClickAt(const FlatHexPosition & click) {
  //Attention, il faudra vérifier si la position est clickable
  if (_controller->selectedPeon() != nullptr){
    _controller->selectedPeon()->setTargetPos(click);
    auto tmp_world = _world->getVectorFromPos(click);
    if (tmp_world != nullptr){
      for (auto peon : *tmp_world){
        LOG_DEBUG("pos : %s target : %s\n",peon->pos().toString().c_str(),peon->targetPos().toString().c_str());
      }
    }
  }
}