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
/// \file   View.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 27 septembre 2020, 20:21
///

#ifndef VIEW_H
#define VIEW_H

#include <gui/Pixel.h>

namespace gui {
  class View {
  protected:

    int _offsetX;     ///< View up left corner X
    int _offsetY;     ///< View up left corner Y
    int _viewWidth;   ///< View width
    int _viewHeight;  ///< View height
    
  public:
    
    View(int ox, int oy, int w, int h) noexcept :
      _offsetX(ox), _offsetY(oy), 
      _viewWidth(w), _viewHeight(h)
    {
    }
    
    /// \brief return true if given pixel is in the view
    bool isInView(const Pixel& p) const noexcept {
      return _offsetX <= p._x && p._x < _viewWidth + _offsetX
          && _offsetY <= p._y && p._y < _viewHeight + _offsetY;
    }
  };
}

#endif /* VIEW_H */

