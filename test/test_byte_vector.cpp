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

#include "../include/byte_vector.h"
#include "../include/word.h"

TEST(TestByteVector, TestConstructor) {
  ByteUtils::ByteVector bytes("0a1b");
  ::testing::internal::CaptureStdout();
  std::cout << bytes;
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "0000101000011011";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestByteVector, TestToHex) {
  ByteUtils::ByteVector bytes("0a1b");
  std::string output = bytes.ToHex();
  std::string expected_output = "0a1b";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestByteVector, TestReturnByteOperator) {
  ByteUtils::ByteVector bytes("0a1b");
  std::string output = bytes[0].ToHex();
  std::string expected_output = "0a";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestByteVector, TestAccessByteOperator) {
  ByteUtils::ByteVector bytes("0a1b");
  bytes[0] = 0xba;
  std::string output = bytes.ToHex();
  std::string expected_output = "ba1b";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestByteVector, TestPushBackWord) {
  ByteUtils::ByteVector bytes("ff");
  ByteUtils::Word word("1a1b1c1d");
  bytes.PushBack(word);
  std::string output = bytes.ToHex();
  std::string expected_output = "ff1a1b1c1d";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestByteVector, TestGetWord) {
  ByteUtils::ByteVector bytes("0a0b0c0d1a1b1c1d");
  ByteUtils::Word word = bytes.GetWord(1);
  std::string output = word.ToHex();
  std::string expected_output = "1a1b1c1d";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestByteWord, TestGetWordVector) {
  ByteUtils::ByteVector bytes("000102030405060708090a0b0c0d0e0f");
  std::vector<ByteUtils::Word> words = bytes.GetWord(1, 2);
  std::string output = "";
  for (const auto& w : words) {
    output += w.ToHex();
  }
  std::string expected_output = "0405060708090a0b";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestByteVector, TestIterator) {
  ByteUtils::ByteVector bytes("0a1b");
  for (auto& byte : bytes) {
    byte = ByteUtils::Byte(0x1b);
  }
  std::string output = bytes.ToHex();
  std::string expected_output = "1b1b";
  ASSERT_STREQ(output.c_str(), expected_output.c_str());

  ::testing::internal::CaptureStdout();
  for (auto it = bytes.begin(); it != bytes.end(); ++it) {
    std::cout << it->ToHex();
  }
  output = ::testing::internal::GetCapturedStdout();
  ASSERT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestByteVector, TestReverseIterator) {
  ByteUtils::ByteVector bytes("0a1b");
  ::testing::internal::CaptureStdout();
  for (auto it = bytes.rbegin(); it != bytes.rend(); ++it) {
    std::cout << it->ToHex();
  }
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "1b0a";
  ASSERT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestByteVector, TestConstIterator) {
  const ByteUtils::ByteVector bytes("0a1b");
  ::testing::internal::CaptureStdout();
  for (const auto& byte : bytes) {
    std::cout << byte.ToHex();
  }
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "0a1b";
  ASSERT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestByteVector, TestConstReverseIterator) {
  const ByteUtils::ByteVector bytes("0a1b");
  ::testing::internal::CaptureStdout();
  for (auto it = bytes.rbegin(); it != bytes.rend(); ++it) {
    std::cout << it->ToHex();
  }
  std::string output = ::testing::internal::GetCapturedStdout();
  std::string expected_output = "1b0a";
  ASSERT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(TestByteVector, TestPushBack) {
  ByteUtils::ByteVector bytes("0a");
  bytes.PushBack(ByteUtils::Byte("1b", 16));
  std::string output = bytes.ToHex();
  std::string expected_output = "0a1b";
  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}