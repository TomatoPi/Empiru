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
/// \file   SoundEngine.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 25 septembre 2020, 20:13
///

#include <cassert>

#include "SoundEngine.h"
#include "utils/log.h"
#include "controller/events/ControllerEvents.h"
#include "entity/peon/PeonEntity.h"

/// \brief Don't do great things
SoundEngine::SoundEngine() : _table() {
  this->registerEvent<EventObjectSelected>(
      [this](const EventObjectSelected & event) -> void {
        if (typeid(Peon) != typeid(*event._ptr))
          return;
        this->playRandomSound(0);
      });
  this->registerEvent<EventObjectAction>(
      [this](const EventObjectAction & event) -> void {
        if (typeid(Peon) != typeid(*event._obj))
          return;
        this->playRandomSound(0);
      });
}
/// \brief Unload sound engine and quit SDL_Mixer
SoundEngine::~SoundEngine() {
  Mix_CloseAudio();
  Mix_Quit();
}
/// \brief Load and Init SDL_Mixer
/// \return nullptr on failure
SoundEngine * SoundEngine::create() {
  
  if (MIX_INIT_OGG != Mix_Init(MIX_INIT_OGG)) {
    LOG_ERROR("Failed start sound engine : %s\n", Mix_GetError());
    return nullptr;
  }
  if (0 != Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024)) {
    LOG_ERROR("Failed open audio : %s\n", Mix_GetError());
    return nullptr;
  }
  Mix_AllocateChannels(64);
  return new SoundEngine();
}

/// \brief Add given sound to the engine's table
/// \brief Return an id that can be used to play it
SoundEngine::SoundId SoundEngine::registerSound(
  std::unique_ptr<SoundAsset> asset) 
{
  SoundId idx(_table.size());
  _table.push_back(std::move(asset));
  return idx;
}

/// \brief Play a random variant of given sound
void SoundEngine::playRandomSound(const SoundId & sound) {
  assert(sound < _table.size() && "Invalid SoundId");
  int err(_table[sound]->play(-1, 0, std::rand() % _table[sound]->count()));
  if (err < 0) {
    LOG_ERROR("%s\n", Mix_GetError());
  }
}