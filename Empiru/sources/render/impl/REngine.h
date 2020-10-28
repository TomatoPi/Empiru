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
/// \file   RenderingEngine.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 10 septembre 2020, 14:56
/// \brief Core object of rendering engine
///
#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include "../IAllocator.h"
#include "gui/Viewport.h"
#include "world/IMap.h"
#include "PixelPerfectBridge.h"
#include <alloc/Allocator.h>

#include <map>
#include <set>

namespace render {
namespace impl {
class REngine: public IAllocator {
private:

  static AssetUIDGen assetUIDGen;

  using Allocator = alloc::IAllocator<ATarget,ATarget::Pointer>;
  using AllocTable =std::unordered_map<AssetUID, Allocator*>;
  using AssetReg = std::unordered_map<AssetUID,std::shared_ptr<Asset>>; // @suppress("Invalid template argument")
  using DrawStack = std::map<gui::Pixel,std::set<ATarget::Pointer,alloc::PtrComp>,gui::Pixel::AscYCompare>;
  using PosList = std::vector<gui::Pixel>;
  using Garbage = std::vector<ATarget::Pointer>;
  using UpdateList = std::vector<ATarget::Pointer>;
  using ObjectsTable = std::unordered_map<game::EUID, ATarget::Pointer>;

  PixelPerfectBridge &_bridge;
  gui::Viewport &_view;
  world::IMap &_world;

  AllocTable _allocs;
  AssetReg _assets;
  ObjectsTable _objects;
  Garbage _garbage;

  DrawStack _stack;
  PosList _tiles;
  UpdateList _updateList;

  ATarget* _tileTarget;
  bool _dirtyStack;

public:

  REngine(PixelPerfectBridge &bridge, gui::Viewport &view,
      world::IMap &world) noexcept;
  virtual ~REngine() noexcept = default;

  void bindSignals() noexcept;

  void render();

  const AssetUID registerAsset(std::shared_ptr<Asset> asset,
      Allocator *alloc) noexcept;

  void setTileTarget(ATarget* target) noexcept;

  ATarget::Pointer createObject(AssetUID kind, ATarget::Builder &builder)
      override;

  void destroyGarbadge() override;

private:
  void updateDrawStack() noexcept;
  void addObject(ATarget::Pointer ptr) noexcept;
  void removeObject(ATarget::Pointer ptr) noexcept;
  void removeFromStack(ATarget::Pointer ptr) noexcept;
  void addToStack(ATarget::Pointer ptr) noexcept;
};
} /* namespace impl */
} /* namespace render */

#endif /* RENDERENGINE_H */
