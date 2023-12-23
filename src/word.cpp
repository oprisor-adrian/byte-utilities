#include "word.h"

#include <sstream>
#include <stdexcept>
#include <regex>

namespace ByteUtils {

Word::Word(const std::string& data) {
  std::regex hex_regex("[0-9a-fA-F]{2}");
  auto regex_begin = std::sregex_iterator(data.begin(), data.end(), hex_regex);
  for (auto it=regex_begin; it!=std::sregex_iterator(); ++it) {
    word_.push_back(Byte(it->str(), 16));
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