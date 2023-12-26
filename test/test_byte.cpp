/* 
  Copyright (C) 2023  Oprișor Adrian-Ilie
  
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
#include <iostream>
#include <stdexcept>
#include <string>

#include "../include/byte.h"

TEST(TestByte, TestConstructor) {
  ASSERT_NO_THROW({ ByteUtils::Byte byte("10101100", 2); });
  ByteUtils::Byte byte("AB", 16);
  std::bitset<8> output = byte.GetByte();
  std::bitset<8> expected_output{"10101011"};
  EXPECT_EQ(output, expected_output);
}

TEST(TestByte, TestConstructorInvalidBase) {
  try {
    ByteUtils::Byte byte("15", 8);
    FAIL() << "Expected exception not thrown.";
  } catch (const std::exception& e) {
    EXPECT_STREQ("Representation can be made only for binary "
                 "or hexadecimal values.", e.what());
  }
}

TEST(TestByte, TestConstructorInvalidHexLength) {
    try {
    ByteUtils::Byte byte("ABC", 16);
    FAIL() << "Expected exception not thrown.";
  } catch (const std::exception& e) {
    EXPECT_STREQ("Given hexadecimal data can't be represented " 
                 "in 1 byte.", e.what());
  }
}

TEST(TestByte, TestConstructorInvalidBitsLength) {
    try {
    ByteUtils::Byte byte("110011011011", 2);
    FAIL() << "Expected exception not thrown.";
  } catch (const std::exception& e) {
    EXPECT_STREQ("Given binary data can't be represented " 
                 "in 1 byte.", e.what());
  }
}

TEST(TestByte, TestStdoutOverloadedOperator) {
  ByteUtils::Byte byte(0xFF);
  ::testing::internal::CaptureStdout();
  std::cout << byte;
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "11111111";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST (TestByte, TestGFMultiplication) {
  ByteUtils::Byte byte1("57", 16);
  ByteUtils::Byte byte2("83", 16);
  ByteUtils::Byte result = byte1 * byte2;
  std::bitset<8> output = result.GetByte();
  std::bitset<8> expected_output{"11000001"};
  EXPECT_EQ(output, expected_output);
}

TEST(TestByte, TestToHex) {
  ByteUtils::Byte byte("11111111", 2);
  std::string output = byte.ToHex();
  std::string expected_output = "ff";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestByte, TestComplementOperation) {
  ByteUtils::Byte byte("10101010", 2);
  ::testing::internal::CaptureStdout();
  std::cout << ~byte;
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "01010101";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestByte, TestIterator) {
  ByteUtils::Byte byte("10101010", 2);
  ::testing::internal::CaptureStdout();
  for (const auto& bit : byte) {
    std::cout << bit;
  }
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "01010101";
  ASSERT_STREQ(output.c_str(), expected_output.c_str());

  for (auto it = byte.begin(); it != byte.end(); ++it) {
    *it = 1;
  }
  ::testing::internal::CaptureStdout();
  std::cout << byte;
  output = ::testing::internal::GetCapturedStdout();
  expected_output = "11111111";
  ASSERT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestByte, TestReverseIterator) {
  ByteUtils::Byte byte("10101010", 2);
  ::testing::internal::CaptureStdout();
  for (auto it = byte.rbegin(); it != byte.rend(); ++it) {
    std::cout << *it;
  }
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string  expected_output = "10101010";
  ASSERT_STREQ(output.c_str(), expected_output.c_str());
}