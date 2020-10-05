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
/// \file   AssetManager.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 30 septembre 2020, 11:29
///

#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <cassert>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

/// \brief Template class used to store assets in a {Type:TypeAsset} dict, and
///   to store specific assets in a {Key:UniqueAsset} dict
template <class Asset, class Manager>
class AssetManager {
private:
  
  /// \brief Dict of assets
  typedef std::unordered_map<std::type_index,Asset> AssetsTable;
  AssetsTable       _table;   ///< Typed assets
  
protected:
  
  /// \brief Basic constructor, register the singleton
  AssetManager() noexcept = default;
  
public:
  
  static Manager& Get() noexcept {
    static Manager _singleton;
    return _singleton;
  }
  /// \brief Basic destructor, release the destructor
  virtual ~AssetManager() noexcept = default;
  
  /// \brief Build in-place a new TypedAsset
  template <typename ...Args>
  Asset& registerAsset(const std::type_info& type, Args&& ...args) {
    auto result(
            _table.emplace(std::type_index(type), 
            Asset(std::forward<Args>(args)...)));
    assert(result.second && "Type already registered");
    return result.first->second;
  }
  
  /// \brief Return the asset associated with this type
  Asset& getAsset(const std::type_info& type) {
    return _table.at(std::type_index(type));
  }
};

#endif /* ASSETMANAGER_H */

