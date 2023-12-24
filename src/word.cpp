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

Word::Word(std::int64_t decimal_value, std::size_t bits) {
  std::vector<std::uint8_t> bytes(
    reinterpret_cast<std::uint8_t*> (&decimal_value),
    reinterpret_cast<std::uint8_t*> (&decimal_value) + sizeof(int64_t)
  );
  for (auto it = bytes.rbegin(); it != bytes.rend(); ++it) {
    word_.push_back(Byte(*it));
  }
}

Word::Word(const std::vector<Byte>& word): word_(word) {}

std::ostream& operator<<(std::ostream& stream, const Word& data) {
  for (const auto& byte : data.word_) {
    stream << byte;
  }
  return stream;
}

Word Word::operator^(const Word& word) const {
  if (word_.size() != word.Size()) {
    throw std::runtime_error("Can't perform XOR operation between words " 
                             "with different sizes.");
  }
  std::vector<Byte> result;
  for (std::size_t index = 0; index < 4; index++) {
    result.push_back(word_[index] ^ word.word_[index]);
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

Word Word::operator&(const Word& word) const {
  if (word_.size() != word.Size()) {
    throw std::runtime_error("Can't perform XOR operation between words " 
                             "with different sizes.");
  }
  std::vector<Byte> result;
  for (std::size_t index = 0; index < word_.size(); index++) {
    result.push_back(word_[index] & word[index]);
  }
  return result;
}

Word Word::operator|(const Word& word) const {
  if (word_.size() != word.word_.size()) {
    throw std::runtime_error("Can't perform XOR operation between words " 
                             "with different sizes.");
  }
  std::vector<Byte> result;
  for (std::size_t index = 0; index < word_.size(); index++) {
    result.push_back(word_[index] | word[index]);
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

Word Word::operator<<(std::size_t n_pos) const {
  Word word = *this;
  for (std::size_t index = 0; index < n_pos; index++) {
    bool carry = false;
    for (auto byte = word.rbegin(); byte != word.rend(); --byte) {
      bool new_carry = (*byte)[7];
      (*byte) <<= 1;
      if (carry) {
        (*byte)[0] = 1;
      }
      carry = new_carry;
    }
  }
  return word;
}

Word Word::operator>>(std::size_t n_pos) const {
  Word word = *this;
  for (std::size_t index = 0; index < n_pos; index++) {
    bool carry = false;
    for (auto& byte : word) {
      bool new_carry = byte[0];
      byte >>= 1;
      if (carry) {
        byte[7] = 1;
      }
      carry = new_carry;
    }
  }
  return word;
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