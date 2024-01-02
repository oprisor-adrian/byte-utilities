/* 
  Copyright (C) 2023-2024  Oprișor Adrian-Ilie
  
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

class ByteTest: public ::testing::Test {
  protected:
    void SetUp() override {
      byte1 = ByteUtils::Byte("10101010", ByteUtils::Base::base_2);
      byte2 = ByteUtils::Byte("11011010", ByteUtils::Base::base_2);
    }
    void TearDown() override {
      byte1 = ByteUtils::Byte("10101010", ByteUtils::Base::base_2);
    }
    ByteUtils::Byte byte1;
    ByteUtils::Byte byte2;
};

TEST(TestByte, TestConstructFromDec) {
  // Tests constructor from decimal values.
  { 
    ByteUtils::Byte byte(255);
    std::bitset<8> output = byte.GetByte();
    std::bitset<8> expected_output{"11111111"};
    ASSERT_EQ(output, expected_output);
  }
  // Tests constructor from hexadecimal values.
  {
    ByteUtils::Byte byte(0x80);
    std::bitset<8> output = byte.GetByte();
    std::bitset<8> expected_output{"10000000"};
    ASSERT_EQ(output, expected_output);
  }
}

TEST(TestByte, TestConstructoFromPlainText) {
  // Tests valid binary data.
  {
    ByteUtils::Byte byte("10101100", ByteUtils::Base::base_2);
    std::bitset<8> output = byte.GetByte();
    std::bitset<8> expected_output{"10101100"};
    ASSERT_EQ(output, expected_output);
  }
  // Tests valid hexadecimal data.
  {
    ByteUtils::Byte byte("ff", ByteUtils::Base::base_16);
    std::bitset<8> output = byte.GetByte();
    std::bitset<8> expected_output{"11111111"};
    ASSERT_EQ(output, expected_output);
  }
  // Tests valid decimal data.
  {
    ByteUtils::Byte byte("255", ByteUtils::Base::base_10);
    std::bitset<8> output = byte.GetByte();
    std::bitset<8> expected_output{"11111111"};
    ASSERT_EQ(output, expected_output);
  }
}

TEST(TestByte, TestConstructorThrowingAtBinaryValues) {
  // Tests larger binary string size.
  {
    try {
      ByteUtils::Byte byte("1010101011", ByteUtils::Base::base_2);
      FAIL() << "Expected to throw.";
    } catch (const std::length_error& e) {
      EXPECT_STREQ(e.what(), "Given binary data is larger than expected.");
    } catch(...) {
      FAIL() << "Expected std::length_error.";
    }
  }
  // Tests invalid characters.
  {
    try {
      ByteUtils::Byte byte("101011fg", ByteUtils::Base::base_2);
      FAIL() << "Expected to throw.";
    } catch (const std::invalid_argument& e) {
      EXPECT_STREQ(e.what(), "Expected only binary characters.");
    } catch (...) {
      FAIL() << "Expected std::invalid_argument.";
    }
  }
}

TEST(TestByte, TestConstructorThrowingAtDecimalValues) {
  // Tests invalid characters.
  {
    try {
      ByteUtils::Byte byte("12f", ByteUtils::Base::base_10);
      FAIL() << "Expected to throw.";
    } catch (const std::invalid_argument& e) {
      EXPECT_STREQ(e.what(), "Expected only numbers.");
    } catch (...) {
      FAIL() << "Expected std::invalid_argument.";
    }
  }
  // Tests larger value.
  {
    try {
      ByteUtils::Byte byte("256", ByteUtils::Base::base_10);
      FAIL() << "Expected to throw.";
    } catch (const std::length_error& e) {
      EXPECT_STREQ(e.what(), "Given decimal data is larger than expected.");
    } catch (...) {
      FAIL() << "Expected std::length_error.";
    }
  }
  // Test negative value.
  {
    try {
      ByteUtils::Byte byte("-126", ByteUtils::Base::base_10);
      FAIL() << "Expect to throw.";
    } catch (const std::invalid_argument& e) {
      EXPECT_STREQ(e.what(), "Expected only numbers.");
    } catch (...) {
      FAIL() << "Expected std::invalid_argument.";
    }
  }
}

TEST(TestByte, TestConstructorThrowingAtHexValues) {
  // Tests larger value.
  {
    try {
      ByteUtils::Byte byte("ffh", ByteUtils::Base::base_16);
      FAIL() << "Expected to throw.";
    } catch (const std::length_error& e) {
      EXPECT_STREQ(e.what(), "Given hexadecimal data is larger than expected.");
    } catch (...) {
      FAIL() << "Expected std::length_error.";
    }
  }
    // Tests invalid characters.
  {
    try {
      ByteUtils::Byte byte("fh", ByteUtils::Base::base_16);
      FAIL() << "Expected to throw.";
    } catch (const std::invalid_argument& e) {
      EXPECT_STREQ(e.what(), "Expected only hexadecimal characters.");
    } catch (...) {
      FAIL() << "Expected std::invalid_argument.";
    }
  }
}

TEST_F(ByteTest, TestStdoutOperator) {
  // Tests operator for %Byte object.
  {
    ::testing::internal::CaptureStdout();
    std::cout << byte1;
    std::string output = ::testing::internal::GetCapturedStdout();
    std::string expected_output = "10101010";
    ASSERT_STREQ(output.c_str(), expected_output.c_str());
  }
  // Test operator for %std::bitset<8>::reference (1 bit).
  {
    std::bitset<8> output_byte = byte1.GetByte();
    ::testing::internal::CaptureStdout();
    for (std::size_t index = 0; index < 8; index++) {
      std::cout << output_byte[index];
    }
    std::string output = ::testing::internal::GetCapturedStdout();
    std::string expected_output = "01010101";
    ASSERT_STREQ(output.c_str(), expected_output.c_str());
  }
}

TEST_F(ByteTest, TestIterator) {
  // Tests ranged-based loop.
  {
    ::testing::internal::CaptureStdout();
    for (const auto& bit : byte1) {
      std::cout << bit;
    }
    std::string output = ::testing::internal::GetCapturedStdout();
    std::string expected_output = "10101010";
    EXPECT_STREQ(output.c_str(), expected_output.c_str()); 
  }
  // Tests iterator-based loop.
  {
    for (auto it = byte1.begin(); it != byte1.end(); ++it) {
      *it = 1;
    }
    ::testing::internal::CaptureStdout();
    std::cout << byte1;
    std::string output = ::testing::internal::GetCapturedStdout();
    std::string expected_output = "11111111";
    EXPECT_STREQ(output.c_str(), expected_output.c_str());
  }
}

TEST_F(ByteTest, TestReverseIterator) {
  ::testing::internal::CaptureStdout();
  for (auto it = byte1.rbegin(); it != byte1.rend(); ++it) {
    std::cout << *it;
  }
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "01010101";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST_F(ByteTest, TestAndOperation) {
  // Tests the AND operation returning new `Byte` object.
  std::bitset<8> output = (byte1 & byte2).GetByte();
  std::bitset<8> expected_output{"10001010"};
  EXPECT_EQ(std::bitset<8>{"10101010"}, byte1.GetByte());
  EXPECT_EQ(std::bitset<8>{"11011010"}, byte2.GetByte());
  EXPECT_EQ(output, expected_output);
  // Tests AND operation with result in the %byte1 object.
  byte1 &= byte2;
  EXPECT_EQ(expected_output, byte1.GetByte());
  EXPECT_EQ(std::bitset<8>{"11011010"}, byte2.GetByte());
}

TEST_F(ByteTest, TestOrOperation) {
  // Tests the OR operation returning new `Byte` object.
  std::bitset<8> output = (byte1 | byte2).GetByte();
  std::bitset<8> expected_output{"11111010"};
  EXPECT_EQ(std::bitset<8>{"10101010"}, byte1.GetByte());
  EXPECT_EQ(std::bitset<8>{"11011010"}, byte2.GetByte());
  EXPECT_EQ(output, expected_output);
  // TEST OR operation with result in the %byte1 object.
  byte1 |= byte2;
  EXPECT_EQ(expected_output, byte1.GetByte());
  EXPECT_EQ(std::bitset<8>{"11011010"}, byte2.GetByte());
}

TEST_F(ByteTest, TestXorOperation) {
  // Tests the XOR operation returning new `Byte` object.
  std::bitset<8> output = (byte1 ^ byte2).GetByte();
  std::bitset<8> expected_output{"01110000"};
  EXPECT_EQ(std::bitset<8>{"10101010"}, byte1.GetByte());
  EXPECT_EQ(std::bitset<8>{"11011010"}, byte2.GetByte());
  EXPECT_EQ(output, expected_output);
  // TEST XOR operation with result in the %byte1 object.
  byte1 ^= byte2;
  EXPECT_EQ(expected_output, byte1.GetByte());
  EXPECT_EQ(std::bitset<8>{"11011010"}, byte2.GetByte());
}

TEST_F(ByteTest, TestComplementOperation) {
  std::bitset<8> output = (~byte1).GetByte();
  std::bitset<8> expected_output{"01010101"};
  EXPECT_EQ(std::bitset<8>{"10101010"}, byte1.GetByte());
  EXPECT_EQ(output, expected_output);
}

TEST_F(ByteTest, TestLeftShifyOperatiion) {
  // Tests left shift operation
  std::bitset<8> output = (byte1 << 1).GetByte();
  std::bitset<8> expected_output{"01010100"};
  EXPECT_EQ(std::bitset<8>{"10101010"}, byte1.GetByte());
  EXPECT_EQ(output, expected_output);
  // Test left shift operation on &byte1 object
  byte1 <<= 1;
  EXPECT_EQ(expected_output, byte1.GetByte());
  // Tests shifting with larger positions.
  EXPECT_THROW({ byte1 << 8; }, std::runtime_error); 
  EXPECT_THROW({ byte1 <<= 8; }, std::runtime_error); 
}

TEST_F(ByteTest, TestRighShiftOperation) {
  // Tests right shift operation
  std::bitset<8> output = (byte1 >> 1).GetByte();
  std::bitset<8> expected_output{"01010101"};
  EXPECT_EQ(std::bitset<8>{"10101010"}, byte1.GetByte());
  EXPECT_EQ(output, expected_output);
  // Test left shift operation on &byte1 object
  byte1 >>= 1;
  EXPECT_EQ(expected_output, byte1.GetByte());
  // Tests shifting with larger positions.
  EXPECT_THROW({ byte1 >> 8; }, std::runtime_error);
  EXPECT_THROW({ byte1 >> 8; }, std::runtime_error); 
}

TEST_F(ByteTest, TestGFMultiplication) {
  std::bitset<8> output = (byte1 * byte2).GetByte();
  std::bitset<8> expected_output{"01000011"};
  EXPECT_EQ(output, expected_output);
}

TEST_F(ByteTest, TestReturnBitOperator) {
  // Tests valid index.
  bool bit = static_cast<bool>(byte1[0]);
  EXPECT_FALSE(bit);
  // Tests invalid index.
  EXPECT_THROW({ byte1[12]; }, std::out_of_range);
}

TEST_F(ByteTest, TestAccesBitOperator) {
  // Tests valid index.
  byte1[0] = 1;
  std::bitset<8> output = byte1.GetByte();
  std::bitset<8> expected_output{"10101011"};
  EXPECT_EQ(output, expected_output);
  // Tests invalid index.
  EXPECT_THROW({ byte2[12] = 1; }, std::out_of_range);
  EXPECT_EQ(byte2.GetByte(), std::bitset<8>{"11011010"});
}

TEST_F(ByteTest, TestComparisonOperators) {
    ByteUtils::Byte byte("10101010", ByteUtils::Base::base_2);
  // Tests equal operator.
  EXPECT_FALSE((byte1 == byte2));
  EXPECT_TRUE((byte1 == byte));
  // Tests not equal operator.
  EXPECT_FALSE((byte1 != byte));
  EXPECT_TRUE((byte1 != byte2));
}

TEST_F(ByteTest, TestIsAnySet) {
  EXPECT_TRUE(byte1.IsAnySet());
  ByteUtils::Byte byte(0x00);
  EXPECT_FALSE(byte.IsAnySet());
}

TEST_F(ByteTest, TestToInt) {
  EXPECT_EQ(byte1.ToInt(), 170);
}

TEST_F(ByteTest, TestToHex) {
  EXPECT_STREQ(byte1.ToHex().c_str(), "aa");
}