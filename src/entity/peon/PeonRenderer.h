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
/// \file   PeonRenderer.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 16 septembre 2020, 12:48
/// \brief Provide PeonRenderer Object
///

#ifndef PEONRENDERER_H
#define PEONRENDERER_H

#include <memory>
#include <unordered_map>
#include "engine/core/entity/Pointer.h"
#include "gui/core/AbstractRenderer.h"
#include "utils/assets/SpriteSheet.h"
#include "utils/assets/GraphicAssetsRegister.h"
#include "utils/misc/Counter.h"

/// \brief Renderer assoaciated with peons
class PeonRenderer : public AbstractRenderer {
private:
  
  struct Datas {
    Datas() : _anim(7,6), _wanim(6,6), _notanim(2,6), _select(false) {}
    SlowCounter _anim;
    SlowCounter _wanim;
    SlowCounter _notanim;
    bool      _select;
  };
    
  /// \brief Animation datas are stored for each attached peon
  typedef std::unordered_map<Pointer,Datas,alloc::PtrHash,alloc::PtrEquals>
    Targets;
  
  std::shared_ptr<SpriteSheet> _sheet;    ///< Basic asset
  std::shared_ptr<SpriteSheet> _mask;     ///< Mask for pixelPerfect click
  std::shared_ptr<SpriteSheet> _select;   ///< Overlay when selected
  std::shared_ptr<SpriteSheet> _whareh;   ///< Attached warehouse icon
  std::shared_ptr<SpriteSheet> _notify;   ///< Notification icons
  Targets                      _targets;  ///< Dict of Animation datas
  
public:
  
  /// \brief Struct used to pass args to PeonRenderer Constructor
  struct SheetsPaths {
    const char* whareh_sheet; ///< WhareHouse overlay
    const char* notify_sheet; ///< Notification icons
  };
  
  /// \brief Constructor
  /// \throw runtime_error on failure
  PeonRenderer(
          const gui::ObjectAsset& assets, 
          const SheetsPaths & args, 
          SDL_Renderer *rdr);
  
  /// \brief Draw a peon on screen, with (x,y) coordinate of bottom's middle
  virtual void renderAt(
    const Pointer& obj, 
    int ori, int x, int y,
    const hex::Viewport & view);
  
  /// \brief Render the object at given position, replacing the texture with
  ///   'color'
  virtual void renderAt(
    const Pointer& obj,
    int ori, int x, int y,
    const hex::Viewport & view,
    const SDL_Color & color); 
  
  /// \brief Called when a new object associated with this renderer is created
  ///  may instanciate fine scope datas, like animation state
  virtual void addTarget(const Pointer& obj) noexcept;
  /// \brief Called when an object associated with this renderer is destroyed
  ///  may dealocate corresponding datas
  virtual void removeTarget(const Pointer& obj) noexcept;
  /// \brief Called when an object associated with this renderer is selected
  ///  may remember draw a special overlay around it
  virtual void targetSelected(const Pointer& obj);
  /// \brief Called when an object associated with this renderer is deselected
  ///  may remember to stop draw special overlay
  virtual void targetDeselected(const Pointer& obj);
};

#endif /* PEONRENDERER_H */
