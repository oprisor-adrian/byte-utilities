/* 
  Copyright (C) 2023 Oprișor Adrian-Ilie
  
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
#include "byte_vector.h"

#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <regex>

#include "word.h"

namespace ByteUtils {

ByteVector::ByteVector(const std::string& hex_string) {
  std::size_t bits_2_represent = hex_string.size() * 4;
  std::string hex_values = hex_string;
  // Checks for incomplete hexadecimal value.
  if (bits_2_represent % 8 != 0) {
    hex_values.insert(0, "0");
  }
  // Represents the %hex_values as binary.
  std::regex hex_regex("[0-9a-fA-F]{2}");
  auto regex_begin = std::sregex_iterator(hex_values.begin(), 
                                          hex_values.end(), 
                                          hex_regex);
  for (auto it=regex_begin; it!=std::sregex_iterator(); ++it) {
    bytes_.emplace_back(it->str(), 16);
  }
}

ByteVector::ByteVector(const std::vector<Byte>& bytes): bytes_(bytes) {}

std::ostream& operator<<(std::ostream& stream, const ByteVector& bytes) {
  for (const auto& byte : bytes) {
    stream << byte;
  }
  return stream;
}

Byte ByteVector::operator[](const std::size_t pos) const {
  if (pos >= bytes_.size()) {
    throw std::out_of_range("The position `pos` is out of range.");
  }
  return bytes_[pos];
}

Byte& ByteVector::operator[](const std::size_t pos) {
  if (pos >= bytes_.size()) {
    throw std::out_of_range("The position `pos` is out of range.");
  }
  return bytes_[pos];
}

void ByteVector::PushBack(const Word& word) {
  for (const auto& byte : word) {
    bytes_.emplace_back(byte);
  }
}

void ByteVector::PushBack(const Byte& byte) {
  bytes_.push_back(byte);
}

Word ByteVector::GetWord(const std::size_t pos) const {
  if (pos >= bytes_.size()/4) {
    throw std::out_of_range("The position `pos` is out of range.");
  }
  std::vector<Byte> word(bytes_.begin()+pos*4, bytes_.begin()+pos*4+4);
  return word;
}

std::vector<Word> ByteVector::GetWord(const std::size_t pos,
                                      const std::size_t count) const {
  std::vector<Word> words;
  for (std::size_t index = 0; index < count; index++) {
    words.emplace_back(GetWord(pos+index));
  }
  return words;
}

std::string ByteVector::ToHex() const {
  std::stringstream stream;
  for (const auto& byte : bytes_) {
    stream << byte.ToHex();
  }
  return stream.str();
}

}  // namespace ByteUtils