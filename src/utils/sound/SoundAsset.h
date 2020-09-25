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
/// \file   SoundAsset.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 15 septembre 2020, 13:12
///

#ifndef SOUNDASSET_H
#define SOUNDASSET_H

#include <string>
#include <vector>
#include <SDL2/SDL_mixer.h>
#include <memory>

/// \brief Basic container and wrapper for SDL_Mixer sound objects
class SoundAsset {
private:
  
  /// \brief A List of loaded sounds
  typedef std::vector<Mix_Chunk*> Sounds;
  Sounds _sounds; ///< Asset's sounds Array
  
public:
  /// \brief release Mix_Chunks
  ~SoundAsset();
  /// \brief Try to load given sound files
  /// Files loaded must be named [path][number][ext]
  /// \param path  : Base path for sound files
  /// \param ext   : extension that follow file number
  /// \param count : Number of sounds files
  /// \return An Asset on success or nullptr if one of file has failed
  static std::unique_ptr<SoundAsset> loadFromFiles(
    const std::string & path, 
    const std::string & ext, 
    const std::size_t & count);
  
  /// \brief Play one of the sounds on given channel
  /// \param channel : the channel to play on, or -1 for the first available
  /// \param loop    : number of loops, -1 for infinite play, 0 to play once
  /// \param sound   : index of the sound to play in this asset
  /// \return -1 on error, the channel the sample is played on otherwise
  int play(const int & channel, const int & loop, const std::size_t & sound);
  /// \brief Return the number of variants available in this asset
  int count() const;
  
private:
  /// \brief Constructor
  SoundAsset(Sounds && sounds);
  friend std::unique_ptr<SoundAsset> std::make_unique<SoundAsset>(Sounds &&);
};

#endif /* SOUNDASSET_H */
