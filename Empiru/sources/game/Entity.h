/*
 * Copyright (C) 2020 tomato
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
/// \file   Entity.h
/// \author tomato
///
/// \date 28 oct. 2020 15:37:30
///
#ifndef SOURCES_GAME_ENTITY_H_
#define SOURCES_GAME_ENTITY_H_

#include "EUID.h"
#include "Decorator.h"
#include <world/IAllocator.h>
#include <render/IAllocator.h>
#include <cassert>
#include <map>

namespace game {

struct EntityBuilder {
  /* world object */
  world::Object::Size size;
  world::Position pos;
  float radius;
  int orientation;
  /* Renderable */
  render::ATarget::Builder *tbuilder;
  /* methods */
  virtual ~EntityBuilder() noexcept = default;
  virtual void operator()(const EUID uid) noexcept {
    /* create the world object and link it */
    world::Object::Pointer object(
        world::IAllocator::Get().createObject(uid, size, pos, radius,
            orientation));
    /* create renderable */
    tbuilder->entity = uid;
    tbuilder->pos = pos;
    tbuilder->ori = orientation;
    render::ATarget::Pointer target(
        render::IAllocator::Get().createObject(*tbuilder));
    /* bind things together */
    object->world::Object::Subject<world::Events::ObjectMoved>::addSubscriber( // @suppress("Method cannot be resolved")
        std::bind_front(
            [](render::ATarget::Pointer ptr, world::Object &obj,
                world::Events::ObjectMoved&) -> void {
              ptr->worldpos(obj.pos());
            }, target));
    object->world::Object::Subject<world::Events::ObjectRotated>::addSubscriber( // @suppress("Method cannot be resolved")
        std::bind_front(
            [](render::ATarget::Pointer ptr, world::Object &obj,
                world::Events::ObjectRotated&) -> void {
              ptr->orientation(obj.orientation());
            }, target));
  }
};

}  // namespace game

#endif /* SOURCES_GAME_ENTITY_H_ */
