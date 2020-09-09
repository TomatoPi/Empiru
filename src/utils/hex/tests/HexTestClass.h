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
 * File:   HexTestClass.h
 * Author: DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 *
 * Created on 9 sept. 2020, 01:28:18
 */

#ifndef HEXTESTCLASS_H
#define HEXTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class HexTestClass : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(HexTestClass);

  CPPUNIT_TEST(testOQOtoGrid);
  CPPUNIT_TEST(testAxialtoOQO);

  CPPUNIT_TEST_SUITE_END();

public:
  HexTestClass();
  virtual ~HexTestClass();
  void setUp();
  void tearDown();

private:
  void testOQOtoGrid();
  void testAxialtoOQO();
};

#endif /* HEXTESTCLASS_H */

