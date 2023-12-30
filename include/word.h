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
#ifndef BYTE_UTILS_WORD_H_
#define BYTE_UTILS_WORD_H_

#include <algorithm>
#include <cstdint>
#include <cmath>
#include <ostream>
#include <string>
#include <array>
#include <regex>

#include "byte.h"

namespace ByteUtils {

// Rounds up to nearest byte.
constexpr std::size_t RoundUp(std::size_t bits) {
  return (bits + 7) / 8;
}

template<std::size_t bits>
class Word;

template<std::size_t bits>
std::ostream& operator<<(std::ostream& stream, const Word<bits>& data);

// The `Word` class manage and performs bitwise operations on 
// 'N' bits of data, treated as a single entity, and stored in 
// little-endian order.
// Example:
//    ByteUtils::Word word1("ffffffff");
//    ByteUtils::Word word2("0a0a0a0a");
//    ByteUtils::Word result = word1 ^ word2;
//    std::cout << result;
template<std::size_t bits>
class Word {
  public:
    // The class `Iterator` provides a mechanism 
    // to traverse a `Word` instance.
    class Iterator {
      public:
        Iterator(std::array<Byte, RoundUp(bits)>& word, std::size_t index)
            : word_(&word), index_(index) {}
        // Move the index towards LSB. 
        inline Iterator& operator++() { ++index_; return *this; }
        // Move the index towards MSB.
        inline Iterator& operator--() { --index_; return *this; }
        // Returns a reference to a byte from the `Word` object.
        inline Byte& operator*() { return (*word_)[index_]; }
        // Returns a pointer to a byte from the `Word` object.
        inline Byte* operator->() { return &(*word_)[index_]; }
        inline bool operator!=(const Iterator& other) const { 
          return word_ != other.word_ || index_ != other.index_; 
        }
      private:
        std::array<Byte, RoundUp(bits)>* word_;
        std::size_t index_;
    };
    // The class `ConstIterator` provides a mechanism
    // to travers a `const Word` instance.
    class ConstIterator {
      public:
        ConstIterator(const std::array<Byte, RoundUp(bits)>& word, 
                      std::size_t index)
            : word_(&word), index_(index) {}
        // Move the index towards LSB. 
        inline ConstIterator& operator++() { ++index_; return *this; }
        // Move the index towards MSB.
        inline ConstIterator& operator--() { --index_; return *this; }
        // Returns a reference to a byte from the `Word` object.
        inline const Byte& operator*() const { return (*word_)[index_]; }
        // Returns a pointer to a byte from the `Word` object.
        inline const Byte* operator->() const { return &(*word_)[index_]; }
        inline bool operator!=(const ConstIterator& other) const { 
          return word_ != other.word_ || index_ != other.index_; 
        }
      private:
        const std::array<Byte, RoundUp(bits)>* word_;
        std::size_t index_;
    };
    // The class `ReverseIterator` provides a mechanism 
    // to traverse a `Word` instance in reverse order.
    class ReverseIterator {
      public:
        ReverseIterator(std::array<Byte, RoundUp(bits)>& word, 
                        std::size_t index)
            : word_(&word), index_(index) {}
        // Move the index towards MSB. 
        inline ReverseIterator& operator++() { --index_; return *this; }
        // Move the index towards LSB.
        inline ReverseIterator& operator--() { ++index_; return *this; }
        // Returns a reference to a byte from the `Word` object.
        inline Byte& operator*() { return (*word_)[index_]; }
        // Returns a pointer to a byte from the `Word` object.
        inline Byte* operator->() { return &(*word_)[index_]; }
        inline bool operator!=(const ReverseIterator& other) const { 
          return word_ != other.word_ || index_ != other.index_; 
        }
      private:
        std::array<Byte, RoundUp(bits)>* word_;
        std::size_t index_;
    };
    // The class `ConstReverseIterator` provides a mechanism
    // to travers a `const Word` instance in reverse order.
    class ConstReverseIterator {
      public:
         ConstReverseIterator(const std::array<Byte, RoundUp(bits)>& word, 
                              std::size_t index)
            : word_(&word), index_(index) {}
        // Move the index towards MSB. 
        inline ConstReverseIterator& operator++() { --index_; return *this; }
        // Move the index towards LSB.
        inline ConstReverseIterator& operator--() { ++index_; return *this; }
        // Returns a reference to a byte from the `Word` object.
        inline const Byte& operator*() const { return (*word_)[index_]; }
        // Returns a pointer to a byte from the `Word` object.
        inline const Byte* operator->() const { return &(*word_)[index_]; }
        inline bool operator!=(const ConstReverseIterator& other) const { 
          return word_ != other.word_ || index_ != other.index_; 
        }
      private:
        const std::array<Byte, RoundUp(bits)>* word_;
        std::size_t index_;
    };
    Word() = default;
    // Creates a `Word` object from a hexadecimal string, 
    // in little-endian order.
    Word(const std::string& hex_string);
    // Creates a `Word` object from given `unsigned long long` data,
    // in little-endian order.
    Word(std::uint64_t data);
    // Initializes the `Word` object with an array of `Byte` objects,
    // in little-endian order.
    Word(const std::array<Byte, RoundUp(bits)>& word);
    Word(const Word& other) = default;
    Word(Word&& other) = default;
    Word& operator=(const Word& other) = default;
    Word& operator=(Word&& other) = default;
    ~Word() = default;
    // Prints the `Word` object as an array of bits.
    friend std::ostream& operator<< <bits>(std::ostream& stream,   
                                           const Word<bits>& data);
    // Returns the `Iterator` that points to the first `Byte` from the `Word`.
    Iterator begin() { return Iterator(word_, 0); }
    // Returns the `Iterator` that points to the last `Byte` from the `Word`.
    Iterator end() { return Iterator(word_, word_.size()); }
    // Returns the `ConstIterator` that points to the first `Byte` 
    // from the `const Word`.
    ConstIterator begin() const { return ConstIterator(word_, 0); }
    // Returns the `ConstIterator` that points to the last `Byte`
    //  from the `const Word`.
    ConstIterator end() const { return ConstIterator(word_, word_.size()); }
    // Returns the `ReverseIterator` that points to the last 
    // `Byte` from the `Word`.
    ReverseIterator rbegin() { return ReverseIterator(word_, word_.size()-1); }
    // Returns the `ReverseIterator` that points to the first 
    // `Byte` from the `cons Word`.
    ReverseIterator rend() { return ReverseIterator(word_, -1); }
    // Returns the `ConstReverseIterator` that points to the last 
    // `Byte` from the `const Word`.
    ConstReverseIterator rbegin() const { 
      return ConstReverseIterator(word_, word_.size()-1); 
    }
    // Returns the `ConstReverseIterator` that points to the first 
    // `Byte` from the `const Word`.
    ConstReverseIterator rend() const { 
      return ConstReverseIterator(word_, -1); 
    }
    // Performs the XOR operation between two `Word` objects.
    Word operator^(const Word& other) const;
    // Performs the XOR operation between `Word` and `Byte` objects.
    Word operator^(const Byte& byte) const;
    // Performs the AND operation between two `Word` objects.
    Word operator&(const Word& word) const; 
    // Performs the OR operation between two `Word` objects.
    Word operator|(const Word& word) const;
    // Performs addition in modulo `2^w`, where `w` is the 
    //numbers of bits.
    Word operator+(const Word& word) const;
    // Returns the complement of the current `Word` object.
    Word operator~() const;
    // Performs left shift bitwise operation by `n_pos` bits.
    Word operator<<(std::size_t n_pos) const;
    // Performs right shift bitwise operation by `n_pos` bits.
    Word operator>>(std::size_t n_pos) const;
    // Returns a byte from position `pos`.
    Byte operator[](const std::size_t pos) const;
    // Accesses the byte from the position `pos`.
    Byte& operator[](const std::size_t pos);
    std::string ToHex() const;
    // Returns the size of `Word` object in bytes.
    inline const std::size_t GetSize() const { return word_.size(); }
    inline const std::array<Byte, RoundUp(bits)>& GetWord() const { return word_; }
  private:
    void CheckValidity(const std::string& hex_string) const;
    std::string PrepareHexString(std::string hex_string) const;
    std::array<Byte, RoundUp(bits)> ParseHexString(
        const std::string& hex_string) const;
    std::array<Byte, RoundUp(bits)> word_;
};

template<std::size_t bits>
Word<bits>::Word(const std::string& hex_string) {
  CheckValidity(hex_string);
  std::string procesed_hex = PrepareHexString(hex_string);
  word_ = ParseHexString(procesed_hex);
}

template<std::size_t bits>
Word<bits>::Word(const std::array<Byte, RoundUp(bits)>& word): word_(word) {}

template<std::size_t bits>
Word<bits>::Word(std::uint64_t decimal_value) {
  std::size_t word_size = RoundUp(bits);
  auto begin = reinterpret_cast<std::uint8_t*>(&decimal_value);
  auto end = reinterpret_cast<std::uint8_t*>(&decimal_value) + word_size;
  std::reverse_copy(begin, end, word_.begin());
}

template<std::size_t bits>
std::ostream& operator<<(std::ostream& stream, const Word<bits>& data) {
  for (const auto& byte : data.GetWord()) {
    stream << byte;
  }
  return stream;
}

template<std::size_t bits>
Word<bits> Word<bits>::operator^(const Word& other) const {
  std::array<Byte, RoundUp(bits)> result;
  for (std::size_t index = 0; index < word_.size(); index++) {
    result[index] = word_[index] ^ other.word_[index];
  }
  return result;
}

template<std::size_t bits>
Word<bits> Word<bits>::operator^(const Byte& byte) const {
  std::array<Byte, RoundUp(bits)> result;
  for (std::size_t index = 0; index < word_.size(); index++) {
    result[index] = word_[index] ^ byte;
  }
  return result;
}

template<std::size_t bits>
Word<bits> Word<bits>::operator&(const Word& other) const {
  std::array<Byte, RoundUp(bits)> result;
  for (std::size_t index = 0; index < word_.size(); index++) {
    result[index] = word_[index] & other.word_[index];
  }
  return result;
}

template<std::size_t bits>
Word<bits> Word<bits>::operator|(const Word& other) const {
  std::array<Byte, RoundUp(bits)> result;
  for (std::size_t index = 0; index < word_.size(); index++) {
    result[index] = word_[index] | other.word_[index];
  }
  return result;
}

template<std::size_t bits>
Word<bits> Word<bits>::operator+(const Word& other) const {
  std::uint64_t nr_1 = 0;
  std::uint64_t nr_2 = 0;
  for (std::size_t index = 0; index < word_.size(); index++) {
    nr_1 = (nr_1 << 8) | word_[index].ToInt();
    nr_2 = (nr_2 << 8) | other.word_[index].ToInt();
  }
  std::uint64_t sum = (nr_1 + nr_2) % (1UL << bits);
  return sum;
}

template<std::size_t bits>
Word<bits> Word<bits>::operator~() const {
  std::array<Byte, RoundUp(bits)> result;
  for (std::size_t index = 0; index < word_.size(); index++) {
    result[index] = ~word_[index];
  }
  return result;
}

template<std::size_t bits>
Word<bits> Word<bits>::operator<<(std::size_t n_pos) const {
  if (n_pos > bits) {
    throw std::out_of_range("n_pos is out of range.");
  }
  Word<bits> word = *this;
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

template<std::size_t bits>
Word<bits> Word<bits>::operator>>(std::size_t n_pos) const {
  if (n_pos > bits) {
    throw std::out_of_range("n_pos is out of range.");
  }
  Word<bits> word = *this;
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

template<std::size_t bits>
Byte Word<bits>::operator[](const std::size_t pos) const {
  if (pos > RoundUp(bits) - 1) {
    throw std::out_of_range("The position `pos` is out of range.");
  }
  return word_[pos];
}

template<std::size_t bits>
Byte& Word<bits>::operator[](const std::size_t pos) {
  if (pos > RoundUp(bits) - 1) {
    throw std::out_of_range("The position `pos` is out of range.");
  }
  return word_[pos];
}

template<std::size_t bits>
std::string Word<bits>::ToHex() const {
  std::stringstream stream;
  for (const auto& byte : word_) {
    stream << byte.ToHex();
  }
  return stream.str();
}

template<std::size_t bits>
void Word<bits>::CheckValidity(const std::string& hex_string) const {
  if (!std::all_of(hex_string.begin(), hex_string.end(), ::isxdigit)) {
    throw std::invalid_argument("Expected only hexadecimal characters.");
  }
}

template<std::size_t bits>
std::string Word<bits>::PrepareHexString(std::string hex_string) const {
  // Round up to nearest byte.
  std::size_t bytes_2_represent = (hex_string.length() * 4 + 7 ) / 8;
  std::size_t word_size = RoundUp(bits);
  // Truncates the %hex_string if is exceeded the size of the word.
  if (word_size < bytes_2_represent) {
    std::cerr << "Input exceeds " << word_size << " bytes. Truncation will be "
                 "applied.";
    std::size_t start_character = (bytes_2_represent - word_size) * 2;
    hex_string = hex_string.substr(start_character, word_size * 2);
  }
  // Adds '0' if %hex_string has incomplete hex value.
  std::size_t input_bits_size = hex_string.length() * 4;
  if ((bits - input_bits_size) % 8 != 0) {
    hex_string.insert(0, "0");
  }
  return hex_string;
}

template<std::size_t bits>
std::array<Byte, RoundUp(bits)> Word<bits>::ParseHexString(
    const std::string& hex_string) const {
  // Rounds up to nearest byte.
  std::size_t word_size = RoundUp(bits);
  std::size_t bytes_2_represent = (hex_string.length() * 4 + 7 ) / 8;
  // Matchs each two hexadecimal characters.
  std::regex hex_regex("[0-9a-fA-F]{2}");
  auto begin = std::sregex_iterator(hex_string.begin(), 
                                    hex_string.end(), 
                                    hex_regex);
  auto end = std::sregex_iterator();
  std::array<Byte, RoundUp(bits)> word;
  auto inserter = word.begin() + (word_size - bytes_2_represent);
  // Parses the hexadecimal values to `Byte` objects.
  std::for_each(begin, end, [&inserter](const std::smatch& match) {
    *(inserter++) = {match.str(), Base::base_16};
  });
  return word;
}

}  // namespace ByteUtils

#endif  // BYTE_UTILS_WORD_H_