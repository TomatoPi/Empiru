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
/// \file   logger.h
/// \author tomato
///
/// \date 30 oct. 2020 02:27:14
///
#ifndef LIBS_ALLOC_HELPERS_LOGGER_H_
#define LIBS_ALLOC_HELPERS_LOGGER_H_

#include "../Allocator.h"
#include <log/log.h>

namespace alloc {

namespace helpers {

template<class Base, class Ptr>
class LoggerDecorator: public IAllocator<Base, Ptr> {
private:
  IAllocator<Base, Ptr> *_alloc;
  std::size_t _count;
public:

  LoggerDecorator(IAllocator<Base, Ptr> *alloc) noexcept :
      _alloc(alloc), _count(0) {
  }
  /// \brief Prevent warning
  virtual ~LoggerDecorator() noexcept = default;

  /// \brief Must create one instance of associated object and return it.
  /// This allocator is the only object's owner, and user should never
  ///   delete them himself.
  /// References returned must be stable (always represent the same object)
  Ptr createObject() override {
    _count++;
    Ptr res(_alloc->createObject());
    LOG::debug("Allocate Object :", typeid(*res).name(),
        "Active objects count :", _count);
    return res;
  }

  /// \brief Must free obj and dealocate associated memory.
  /// Must be the only way used to destroy objects
  void deleteObject(Ptr ptr) override {
    _count--;
    LOG::debug("Release Object :", typeid(*ptr).name(),
        "Active objects count :", _count);
    _alloc->deleteObject(ptr);
  }

  /// \brief Must call given callback on each object
  ///   Callback parameters are the object and the associated reference
  /// \warning Delete objects inside the callback may cause undefined behaviour
  void foreach(std::function<void(Base &obj)> func) override {
    _alloc->foreach(func);
  }
};

}  // namespace helpers

}  // namespace alloc

#endif /* LIBS_ALLOC_HELPERS_LOGGER_H_ */
