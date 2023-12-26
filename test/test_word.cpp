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

#include <iostream>
#include <string>
#include <vector>

#include "../include/byte.h"
#include "../include/word.h"

TEST(TestWord, TestHexStringConstructor) {
  ByteUtils::Word word("1a1b1cf");
  ::testing::internal::CaptureStdout();
  std::cout << word;
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "00000001101000011011000111001111";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestDecimalValueConstructor) {
  ByteUtils::Word word(24, 64);
  ::testing::internal::CaptureStdout();
  std::cout << word;
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "0000000000000000000000000000000000000000000000000000000000011000";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestStdouOverloadedOperator) {
  ByteUtils::Word word("abffcdaf");
  ::testing::internal::CaptureStdout();
  std::cout << word;
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "10101011111111111100110110101111";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestWordXorOperation) {
  ByteUtils::Word word1("ffffffff");
  ByteUtils::Word word2("0a0a0a0a");
  ByteUtils::Word result = word1 ^ word2;
  ::testing::internal::CaptureStdout();
  std::cout << result;
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "11110101111101011111010111110101";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestInvalidWordXorOperation) {
  ByteUtils::Word word1("ffffffff");
  ByteUtils::Word word2("0a0a0a0a", 64);
  EXPECT_THROW({ByteUtils::Word result = word1 ^ word2;}, std::runtime_error);
}

TEST(TestWord, TestWordByteXorOperation) {
  ByteUtils::Word word("ffffffff");
  ByteUtils::Byte byte(0x01);
  ByteUtils::Word result = word ^ byte;
  ::testing::internal::CaptureStdout();
  std::cout << result;
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "11111110111111101111111011111110";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestWordAndOperation) {
  ByteUtils::Word w1("ff");
  ByteUtils::Word w2("00");
  ByteUtils::Word result = w1 & w2;
  std::string output = result.ToHex();
  std::string expected_output = "00000000";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestWordOrOperator) {
  ByteUtils::Word w1("ff");
  ByteUtils::Word w2("00");
  ByteUtils::Word result = w1 | w2;
  std::string output = result.ToHex();
  std::string expected_output = "000000ff";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestReturnByteOperator) {
  ByteUtils::Word word("0aff0abc");
  ASSERT_THROW(word[-1], std::out_of_range);
  ByteUtils::Byte byte = word[1];
  std::bitset<8> output = byte.GetByte();
  std::bitset<8> expected_output{"11111111"};
  EXPECT_EQ(output, expected_output);
}

TEST(TestWord, TestAccesByteOPerator) {
  ByteUtils::Word word("0aff0abc");
  ASSERT_THROW(word[4], std::out_of_range);
  word[1] = ByteUtils::Byte(0x0a);
  ::testing::internal::CaptureStdout();
  std::cout << word;
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "00001010000010100000101010111100";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestToHex) {
  ByteUtils::Word word("0aff0abc");
  word[3] = ByteUtils::Byte(0x0a);
  std::string output = word.ToHex();
  std::string expected_output = "0aff0a0a";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestComplementOperator) {
  ByteUtils::Word word("ffff");
  ::testing::internal::CaptureStdout();
  std::cout << ~word;
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "11111111111111110000000000000000";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestIterator) {
  ByteUtils::Word word("ffff");
  ::testing::internal::CaptureStdout();
  for (const auto& byte : word) {
    std::cout << byte.ToHex();
  }
  std::string expected_output = "0000ffff";;
  std::string output = ::testing::internal::GetCapturedStdout();
  ASSERT_STREQ(output.c_str(), expected_output.c_str());

  for (auto it = word.begin(); it != word.end(); ++it) {
    *it = ByteUtils::Byte(0x80);
  }
  output = word.ToHex();
  expected_output = "80808080";
  ASSERT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestReverseIterator) {
  ByteUtils::Word word("ffff");
  ::testing::internal::CaptureStdout();
  for (auto it = word.rbegin(); it != word.rend(); ++it) {
    std::cout << (*it).ToHex();
  }
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "ffff0000";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestLeftShiftOperator) {
  ByteUtils::Word word("ff");
  ByteUtils::Word result = word << 1;
  std::string output = result.ToHex();
  std::string expected_output = "000001fe";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestRightShiftOperator) {
  ByteUtils::Word word("ff");
  ByteUtils::Word result = word >> 1;
  std::string output = result.ToHex();
  std::string expected_output = "0000007f";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestConstIterator) {
  const ByteUtils::Word word("ffff");
  ::testing::internal::CaptureStdout();
  for (const auto& byte : word) {
    std::cout << byte.ToHex();
  }
  std::string expected_output = "0000ffff";;
  std::string output = ::testing::internal::GetCapturedStdout();
  ASSERT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestConstReverseIterator) {
  const ByteUtils::Word word("ffff");
  ::testing::internal::CaptureStdout();
  for (auto it = word.rbegin(); it != word.rend(); ++it) {
    std::cout << (*it).ToHex();
  }
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "ffff0000";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestWord, TestPushBack) {
  ByteUtils::Word word;
  word.PushBack(ByteUtils::Byte("ff", 16));
  std::string output = word.ToHex();
  std::string expected_output = "ff";
  EXPECT_STREQ(output.c_str(), expected_output.c_str()); 
}