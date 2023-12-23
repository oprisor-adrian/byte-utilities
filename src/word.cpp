#include "word.h"

#include <regex>
#include <sstream>
#include <stdexcept>

namespace ByteUtils {

Word::Word(const std::string& hex_string, const std::size_t bits) {
  if (bits < hex_string.length() * 4) {
    std::cerr << "Given hexadecimal value is larger than " + 
                 std::to_string(bits) + 
                 " bits. The truncations will be applied." << std::endl;
  }
  std::string hex_values = hex_string.substr(0, bits / 4);
  // Checks for incomplete 8 bits hexadecimal value.
  std::size_t bits_length = hex_string.length() * 4;
  if ((bits - bits_length) % 8 != 0) {
    hex_values.insert(0, "0");
  }
  // Adds the hexadecimal values as `Byte` objects.
  std::regex hex_regex("[0-9a-fA-F]{2}");
  auto regex_begin = std::sregex_iterator(hex_values.begin(), 
                                          hex_values.end(), 
                                          hex_regex);
  for (auto it=regex_begin; it!=std::sregex_iterator(); ++it) {
    word_.push_back(Byte(it->str(), 16));
  }
  // Fills the missing bytes with '0x00'.
  for (std::size_t index = 0; index < (bits - bits_length) / 8; index++) {
    word_.insert(word_.begin(), Byte(0x00));
  }
}

Word::Word(const std::vector<Byte>& word): word_(word) {}

std::ostream& operator<<(std::ostream& stream, const Word& data) {
  for (const auto& byte : data.GetWord()) {
    stream << byte;
  }
  return stream;
}

Word Word::operator^(const Word& word) const {
  if (word_.size() != word.GetSize()) {
    throw std::runtime_error("Can't perform XOR operation between words " 
                             "with different sizes.");
  }
  std::vector<Byte> result;
  for (std::size_t index = 0; index < 4; index++) {
    result.push_back(word_[index] ^ word.GetWord()[index]);
  }
  return result;
}

Word Word::operator^(const Byte& byte) const {
  std::vector<Byte> result;
  for (std::size_t index = 0; index < 4 ; index++) {
    result.push_back(word_[index] ^ byte);
  }
  return result;
}

Word Word::operator~() const {
  ByteUtils::Word complement;
  for (const auto& w : word_) {
    complement.word_.push_back(~w);
  }
  return complement;
}

Byte Word::operator[](const std::size_t pos) const {
  if (pos >= 4 || pos < 0) {
    throw std::out_of_range("The position `pos` is out of range.");
  }
  return word_[pos];
}

Byte& Word::operator[](const std::size_t pos) {
  if (pos >= 4 || pos < 0) {
    throw std::out_of_range("The position `pos` is out of range.");
  }
  return word_[pos];
}

std::string Word::ToHex() const {
  std::stringstream stream;
  for (const auto& byte : word_) {
    stream << byte.ToHex();
  }
  return stream.str();
}

}  // namespace ByteUtils