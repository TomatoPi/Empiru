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
/// \file   SoundAsset.cpp
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 15 septembre 2020, 13:12
///

#include <cassert>

#include "SoundAsset.h"
#include "utils/log.h"

/// \brief Constructor
SoundAsset::SoundAsset(Sounds&& sounds) :
  _sounds(sounds)
{
  
}
/// \brief release Mix_Chunks
SoundAsset::~SoundAsset() {
  for (auto chunk : _sounds) {
    Mix_FreeChunk(chunk);
  }
}
/// \brief Try to load given sound files
/// Files loaded must be named [path][number][ext]
/// \param path  : Base path for sound files
/// \param ext   : extension that follow file number
/// \param count : Number of sounds files
/// \return An Asset on success or nullptr if one of file has failed
std::unique_ptr<SoundAsset> SoundAsset::loadFromFiles(
    const std::string& path, 
    const std::string& ext, 
    const std::size_t& count)
{
  Sounds sounds(count, nullptr);
  for (std::size_t i(0) ; i<count ; ++i) {
    std::string file = path + std::to_string(i) + ext;
    Mix_Chunk * tmp(Mix_LoadWAV(file.c_str()));
    if (!tmp) {
      LOG_ERROR("%s : %s\n", path.c_str(), Mix_GetError());
      for (auto chunk : sounds) {
        Mix_FreeChunk(chunk);
      }
    }
    sounds[i] = tmp;
  }
  return std::make_unique<SoundAsset>(std::move(sounds));
}

/// \brief Play one of the sounds on given channel
/// \param channel : the channel to play on, or -1 for the first available
/// \param loop    : number of loops, -1 for infinite play, 0 to play once
/// \param sound   : index of the sound to play in this asset
/// \return -1 on error, the channel the sample is played on otherwise
int SoundAsset::play(
    const int channel, 
    const int loop, 
    const std::size_t & sound) 
{
  assert(-1 <= channel && "Invalid Play channel");
  assert(-1 <= loop && "Invalid loop count");
  assert(sound < _sounds.size() && "Invalid Sound Index");
  return Mix_PlayChannel(channel, _sounds[sound], loop);
}
/// \brief Return the number of variants available in this asset
int SoundAsset::count() const {
  return _sounds.size();
}