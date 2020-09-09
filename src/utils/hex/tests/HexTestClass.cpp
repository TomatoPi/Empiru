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

/*
 * File:   HexTestClass.cpp
 * Author: DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 *
 * Created on 9 sept. 2020, 01:28:20
 */

#include "HexTestClass.h"
#include "utils/hex/HexCoords.h"


CPPUNIT_TEST_SUITE_REGISTRATION(HexTestClass);

HexTestClass::HexTestClass() {
}

HexTestClass::~HexTestClass() {
}

void HexTestClass::setUp() {
}

void HexTestClass::tearDown() {
}

void HexTestClass::testOQOtoGrid() {
  CPPUNIT_ASSERT(true);
}

void HexTestClass::testAxialtoOQO() {
  AxialPosition a{0,0}, b{1,1}, c{-2,1}, d{2,4}, e{1,3};
  OQOffsetPosition w{0,0}, x{1,1}, y{-2, 1}, z{0,4}, u{0,3}, of;
  
  convertPosition(a, &of);
  CPPUNIT_ASSERT(of == w);
  
  convertPosition(b, &of);
  CPPUNIT_ASSERT(of == x);
  
  convertPosition(c, &of);
  CPPUNIT_ASSERT(of == y);
  
  convertPosition(d, &of);
  CPPUNIT_ASSERT(of == z);
  
  convertPosition(e, &of);
  CPPUNIT_ASSERT(of == u);
}

