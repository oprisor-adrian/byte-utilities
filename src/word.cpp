#include "word.h"

#include <regex>
#include <sstream>
#include <stdexcept>

namespace ByteUtils {

Word::Word(const std::string& hex_string, const std::size_t bits) {
  std::string hex_values = hex_string;
  // Rounds up to nearest byte. 
  std::size_t bytes_2_represent = (bits + 7) / 8;
  std::size_t input_byte_size = (hex_string.length() * 4 + 7 ) / 8;
  // Truncates the %hex_string if needed.
  if (bytes_2_represent < input_byte_size) {
    std::cerr << "Input exceeds " + bytes_2_represent << " bytes. It will be"
                 " truncated."; 
    hex_values.substr(0, bytes_2_represent * 2);
  }
  // Completes the odd %hex_string size.
  std::size_t input_bits_size = hex_values.length() * 4;
  if ((bits - input_bits_size) % 8 != 0) {
    hex_values.insert(0, "0");
  }
  // Adds the hexadecimal values as `Byte` objects.
  std::regex hex_regex("[0-9a-fA-F]{2}");
  auto regex_begin = std::sregex_iterator(hex_values.begin(), 
                                          hex_values.end(), 
                                          hex_regex);
  for (auto it=regex_begin; it!=std::sregex_iterator(); ++it) {
    word_.emplace_back(it->str(), 16);
  }
  // Fills the missing bytes with '0x00'.
  std::size_t missing_bytes = bytes_2_represent - input_byte_size;
  word_.insert(word_.begin(), missing_bytes, Byte(0x00));
}

Word::Word(std::int64_t decimal_value, std::size_t bits) {
  std::vector<std::uint8_t> bytes(
    reinterpret_cast<std::uint8_t*> (&decimal_value),
    reinterpret_cast<std::uint8_t*> (&decimal_value) + sizeof(int64_t)
  );
  // Round up to nearest byte.
  std::size_t bytes_2_represent = (bits + 7) / 8;
  auto begin = bytes.rbegin();
  auto end = bytes.rbegin() + bytes_2_represent;
  for (auto it = begin; it != end; ++it) {
    word_.emplace_back(*it);
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
    result.emplace_back(word_[index] ^ word.word_[index]);
  }
  return result;
}

Word Word::operator^(const Byte& byte) const {
  std::vector<Byte> result;
  for (std::size_t index = 0; index < 4 ; index++) {
    result.emplace_back(word_[index] ^ byte);
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
    result.emplace_back(word_[index] & word[index]);
  }
  return result;
}

Word Word::operator|(const Word& word) const {
  if (word_.size() != word.Size()) {
    throw std::runtime_error("Can't perform XOR operation between words " 
                             "with different sizes.");
  }
  std::vector<Byte> result;
  for (std::size_t index = 0; index < word_.size(); index++) {
    result.emplace_back(word_[index] | word[index]);
  }
  return result;
}

Word Word::operator~() const {
  std::vector<Byte> result;
  for (const auto& w : word_) {
    result.emplace_back(~w);
  }
  return result;
}

Word Word::operator<<(std::size_t n_pos) const {
  if (n_pos > word_.size() * 8) {
    throw std::out_of_range("n_pos is out of range.");
  }
  Word word = *this;
  while (n_pos--) {
    bool carry = false;
    for (auto byte = word.rbegin(); byte != word.rend(); ++byte) {
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
  if (n_pos > word_.size() * 8) {
    throw std::out_of_range("n_pos is out of range.");
  }
  Word word = *this;
  while (n_pos--) {
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
  if (pos > 3) {
    throw std::out_of_range("The position `pos` is out of range.");
  }
  return word_[pos];
}

Byte& Word::operator[](const std::size_t pos) {
  if (pos > 3) {
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