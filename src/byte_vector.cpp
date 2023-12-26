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
  // Checks for incomplete hexadecimal values.
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
  for (const auto& byte : bytes.bytes_) {
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
  for (const auto& byte : word.GetWord()) {
    bytes_.emplace_back(byte);
  }
}

Word ByteVector::GetWord(const std::size_t pos) const {
  if (pos >= bytes_.size()/4 || pos < 0) {
    throw std::out_of_range("The position `pos` is out of range.");
  }
  std::vector<Byte> word(bytes_.begin()+pos*4, bytes_.begin()+pos*4+4);
  return word;
}

std::vector<Word> ByteVector::GetWord(const std::size_t pos,
                                      const std::size_t count) const {
  std::vector<Word> words;
  for (std::size_t index = 0; index < count; index++) {
    words.push_back(GetWord(pos+index));
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