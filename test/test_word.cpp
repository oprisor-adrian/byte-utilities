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

#include <array>
#include <iostream>
#include <string>

#include "../include/byte.h"
#include "../include/word.h"

class WordTest: public ::testing::Test {
  protected:
    void SetUp() override {
      word1 = ByteUtils::Word<32>("ffffffff");
      word2 = ByteUtils::Word<32>(0x1a1b1c1d);
    }
    void TearDown() override {
      word1 = ByteUtils::Word<32>("ffffffff");
    }
    ByteUtils::Word<32> word1;
    ByteUtils::Word<32> word2;
};

TEST(TestWord, TestConstructorFromHexString) {
  // Tests the representation on 32 bits.
  {
    ByteUtils::Word<32> word("ff");
    std::array<ByteUtils::Byte, 4> output = word.GetWord();
    std::array<ByteUtils::Byte, 4> expected_output = { 0x00, 0x00, 0x00, 0xff };
    ASSERT_EQ(output, expected_output);
  }
  // Tests the representation on 64 bits.
  {
    ByteUtils::Word<64> word("ff");
    std::array<ByteUtils::Byte, 8> output = word.GetWord();
    std::array<ByteUtils::Byte, 8> expected_output = { 0x00, 0x00, 0x00, 0x00,
                                                       0x00, 0x00, 0x00, 0xff };
    ASSERT_EQ(output, expected_output);
  }
  // Tests with imcomplete hexadecimal string.
  {
    ByteUtils::Word<32> word("faf");
    std::array<ByteUtils::Byte, 4> output = word.GetWord();
    std::array<ByteUtils::Byte, 4> expected_output = { 0x00, 0x00, 0x0f, 0xaf };
    ASSERT_EQ(output, expected_output);
  }
  // Tests with complete hexadecimal string.
  {
    ByteUtils::Word<32> word("fafafafa");
    std::array<ByteUtils::Byte, 4> output = word.GetWord();
    std::array<ByteUtils::Byte, 4> expected_output = { 0xfa, 0xfa, 0xfa, 0xfa };
    ASSERT_EQ(output, expected_output);
  }
  // Tests trucation of larger hexadecimal string.
  {
    ::testing::internal::CaptureStderr();
    ByteUtils::Word<32> word("abfafafafa");
    std::string cerr_msg = ::testing::internal::GetCapturedStderr();
    std::string expected_cerr_msg = "Input exceeds 4 bytes. Truncation will be applied.";
    ASSERT_EQ(cerr_msg, expected_cerr_msg);
    std::array<ByteUtils::Byte, 4> output = word.GetWord();
    std::array<ByteUtils::Byte, 4> expected_output = { 0xfa, 0xfa, 0xfa, 0xfa };
    ASSERT_EQ(output, expected_output);
  }
  // Tests with empty string.
  {
    ByteUtils::Word<32> word("");
    std::array<ByteUtils::Byte, 4> output = word.GetWord();
    std::array<ByteUtils::Byte, 4> expected_output = { 0x00, 0x00, 0x00, 0x00 };
  }
    // Tests when throwing.
  {
    EXPECT_THROW({ ByteUtils::Word<32> word("fft"); }, std::invalid_argument);
  }
}

TEST(TestWord, TestConstuctorFromDecimalValue) {
  // Tests the representation on 32 bits.
  {
    ByteUtils::Word<32> word(255);
    std::array<ByteUtils::Byte, 4> output = word.GetWord();
    std::array<ByteUtils::Byte, 4> expected_output = { 0x00, 0x00, 0x00, 0xff };
    ASSERT_EQ(output, expected_output);
  }
  // Tests the representation on 64 bits.
  {
    ByteUtils::Word<64> word(512);
    std::array<ByteUtils::Byte, 8> output = word.GetWord();
    std::array<ByteUtils::Byte, 8> expected_output = { 0x00, 0x00, 0x00, 0x00,
                                                       0x00, 0x00, 0x02, 0x00 };
    ASSERT_EQ(output, expected_output);
  }
  // Tests with hexadecimal value on 32 bits representation.
  {
    ByteUtils::Word<32> word(0x1a1b1c);
    std::array<ByteUtils::Byte, 4> output = word.GetWord();
    std::array<ByteUtils::Byte, 4> expected_output = { 0x00, 0x1a, 0x1b, 0x1c };
    ASSERT_EQ(output, expected_output);
  }
  // Tests with binary value on 32 bits representation.
  {
    ByteUtils::Word<32> word(0b10101010);
    std::array<ByteUtils::Byte, 4> output = word.GetWord();
    std::array<ByteUtils::Byte, 4> expected_output = { 0x00, 0x00, 0x00, 0xaa };
    ASSERT_EQ(output, expected_output);
  }
}

TEST_F(WordTest, TestStdoutOperator) {
  ::testing::internal::CaptureStdout();
  std::cout << word1;
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "11111111111111111111111111111111";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST_F(WordTest, TestIterator) {
  // Tests range-based loop.
  {
    ::testing::internal::CaptureStdout();
    for (const auto& byte : word1) {
      std::cout << byte.ToHex();
    }
    std::string output = ::testing::internal::GetCapturedStdout();
    std::string expected_output = "ffffffff";
    EXPECT_STREQ(output.c_str(), expected_output.c_str());
  }
  // Tests iterator-based loop.
  {
    for (auto it = word1.begin(); it != word1.end(); ++it) {
      *it = {"01", ByteUtils::Base::base_16};
    }
    std::array<ByteUtils::Byte, 4> output = word1.GetWord();
    std::array<ByteUtils::Byte, 4> expected_output = { 0x01, 0x01, 0x01, 0x01 };
    EXPECT_EQ(output, expected_output);
  }
}

TEST(TestWord, TestConstIterator) {
  const ByteUtils::Word<32> word(0x1a1b);
  std::string expected_output = "00001a1b";
  // Tests iterator-base loop
  {
    ::testing::internal::CaptureStdout();
    for (auto it = word.begin(); it != word.end(); ++it) {
      std::cout << it->ToHex();
    }
    std::string output = ::testing::internal::GetCapturedStdout();
    EXPECT_STREQ(output.c_str(), expected_output.c_str());
  }
  // Tests range-base loop
  {
    ::testing::internal::CaptureStdout();
    for (const auto& byte : word) {
      std::cout << byte.ToHex();
    }
    std::string output = ::testing::internal::GetCapturedStdout();
    EXPECT_STREQ(output.c_str(), expected_output.c_str());
  }
}

TEST_F(WordTest, TestReverseIterator) {
  ::testing::internal::CaptureStdout();
  for (auto it = word2.rbegin(); it != word2.rend(); ++it) {
    std::cout << it->ToHex();
  }
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "1d1c1b1a";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestConstReverseIterator) {
  const ByteUtils::Word<32> word(0x1a1b);
  ::testing::internal::CaptureStdout();
  for (auto it = word.rbegin(); it != word.rend(); ++it) {
    std::cout << it->ToHex();
  }
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "1b1a0000";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST_F(WordTest, TestXorOperator) {
  // Tests XOR operation between two `Word` objects.
  {
    std::array<ByteUtils::Byte, 4> output = (word1 ^ word2).GetWord();
    std::array<ByteUtils::Byte, 4> expected_output = { 0b11100101, 0b11100100, 
                                                       0b11100011, 0b11100010 };
    EXPECT_EQ(output, expected_output);
  }
  // Tests XOR operation between `Word` and `Byte`.
  {
    ByteUtils::Byte byte(0xff);
    std::array<ByteUtils::Byte, 4> output = (word1 ^ byte).GetWord();
    std::array<ByteUtils::Byte, 4> expected_output = { 0x00, 0x00, 0x00, 0x00 };
    EXPECT_EQ(output, expected_output);
  }
}

TEST_F(WordTest, TestAndOperator) {
  std::array<ByteUtils::Byte, 4> output = (word1 & word2).GetWord();
  std::array<ByteUtils::Byte, 4> expected_output = { 0b00011010, 0b00011011, 
                                                     0b00011100, 0b00011101 };
  EXPECT_EQ(output, expected_output);
}

TEST_F(WordTest, TestOrOperator) {
  std::array<ByteUtils::Byte, 4> output = (word1 | word2).GetWord();
  std::array<ByteUtils::Byte, 4> expected_output = { 0xff, 0xff, 0xff, 0xff };
  EXPECT_EQ(output, expected_output);
}

TEST_F(WordTest, TestAdditionOperator) {
  std::array<ByteUtils::Byte, 4> output = (word1 + word2).GetWord();
  std::array<ByteUtils::Byte, 4> expected_output = { 0x1a, 0x1b, 0x1c, 0x1c };
  EXPECT_EQ(output, expected_output);
}

TEST_F(WordTest, TestComplementOperator) {
  std::array<ByteUtils::Byte, 4> output = (~word1).GetWord();
  std::array<ByteUtils::Byte, 4> expected_output = { 0x00, 0x00, 0x00, 0x00 };
  EXPECT_EQ(output, expected_output);
}

TEST_F(WordTest, TestLeftShiftOperator) {
  std::array<ByteUtils::Byte, 4> output = (word1 << 1).GetWord();
  std::array<ByteUtils::Byte, 4> expected_output = { 0xff, 0xff, 0xff, 0xfe };
  EXPECT_EQ(output, expected_output);
}

TEST_F(WordTest, TestRighShiftOperator) {
  std::array<ByteUtils::Byte, 4> output = (word1 >> 1).GetWord();
  std::array<ByteUtils::Byte, 4> expected_output = { 0x7f, 0xff, 0xff, 0xff };
  EXPECT_EQ(output, expected_output);
}

TEST_F(WordTest, TestReturnOperator) {
  ByteUtils::Byte first_byte = word1[0];
  ByteUtils::Byte last_byte = word1[3];
  EXPECT_THROW({ word1[4]; }, std::out_of_range);
}

TEST_F(WordTest, TestAccessOperator) {
  word1[0] = 0x00;
  EXPECT_THROW({ word1[4] = 0x00; }, std::out_of_range);
  std::array<ByteUtils::Byte, 4> output = word1.GetWord();
  std::array<ByteUtils::Byte, 4> expected_output = { 0x00, 0xff, 0xff, 0xff };
  EXPECT_EQ(output, expected_output); 
}

TEST_F(WordTest, TestToHex) {
  std::string output = word2.ToHex();
  std::string expected_output = "1a1b1c1d";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}