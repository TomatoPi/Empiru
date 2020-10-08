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
/// \file   SoundEngine.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 25 septembre 2020, 20:13
///

#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H

#include <memory>
#include <vector>
#include "utils/core/Observer.h"
#include "utils/sound/SoundAsset.h"

class SoundEngine : public Observer {
public:
  
  /// \brief Object that will be used to refer a specific asset;
  typedef std::size_t SoundId;
  
private:
  
  typedef std::vector<std::unique_ptr<SoundAsset>> SoundsTable;
  SoundsTable _table;
  
public:
  
  /// \brief Unload sound engine and quit SDL_Mixer
  ~SoundEngine();
  /// \brief Load and Init SDL_Mixer
  /// \return nullptr on failure
  static SoundEngine * create();
  
  /// \brief Add given sound to the engine's table
  /// \brief Return an id that can be used to play it
  SoundId registerSound(std::unique_ptr<SoundAsset> asset);
  
  /// \brief Play a random variant of given sound
  void playRandomSound(const SoundId & sound);
  
private:
  
  /// \brief Don't do great things
  SoundEngine();
  friend std::unique_ptr<SoundEngine> std::make_unique<SoundEngine>();
};

#endif /* SOUNDENGINE_H */
