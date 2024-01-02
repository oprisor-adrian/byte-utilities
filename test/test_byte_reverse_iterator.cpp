/* 
  Copyright (C) 2023-2024 Oprișor Adrian-Ilie
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
   
  Contact: contact@dev-adrian.com
*/
#include <gtest/gtest.h>

#include <bitset>

#include "../include/byte.h"

class ReverseIteratorTest: public ::testing::Test {
  protected:
    void SetUp() override {
      // Reads bites in little-endian format.
      byte = std::bitset<8>{"01010101"};
    }
    void TearDown() override {
      // Reads bites in little-endian format.
      byte = std::bitset<8>{"01010101"};
    }
    std::bitset<8> byte;
};

TEST_F(ReverseIteratorTest, TestReferenceOperator) {
  // Assigns value using the reference.
  {
    ByteUtils::Byte::ReverseIterator it(byte, 6);
    *it = 0;
    std::bitset<8> expected_output{"00010101"};
    EXPECT_EQ(byte, expected_output);
  }
  // Returns constant reference.
  {
    ByteUtils::Byte::ReverseIterator it(byte, 6);
    bool output = *it;
    bool expected_output = 0;
    EXPECT_EQ(output, expected_output);
  }
  // Tests when throw.
  {
    ByteUtils::Byte::ReverseIterator it(byte, 9);
    EXPECT_THROW(*it, std::out_of_range);
  }
}

TEST_F(ReverseIteratorTest, TestPrefixIncrementor) {
  ByteUtils::Byte::ReverseIterator it(byte, 5);
  ++it;
  bool output = *it;
  bool expected_output = 1;
  EXPECT_EQ(output, expected_output);
}

TEST_F(ReverseIteratorTest, TestPrefixDecrementor) {
  ByteUtils::Byte::ReverseIterator it(byte, 2);
  --it;
  bool output = *it;
  bool expected_output = 0;
  EXPECT_EQ(output, expected_output);
}

TEST_F(ReverseIteratorTest, TestComparisonOperator) {
  {
    ByteUtils::Byte::ReverseIterator it1(byte, 3);
    ByteUtils::Byte::ReverseIterator it2(byte, 3);
    EXPECT_FALSE(it1 != it2);
  }
  {
    ByteUtils::Byte::ReverseIterator it1(byte, 0);
    std::bitset<8> temp_bits{"11010101"};
    ByteUtils::Byte::ReverseIterator it2(temp_bits, 0);
    EXPECT_TRUE(it1 != it2);
  }
}