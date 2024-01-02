/* 
  Copyright (C) 2023-2024 Oprișor Adrian-Ilie
  
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
#include "byte.h"

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace ByteUtils {

Byte::Iterator::Iterator(std::bitset<8>& bits, std::size_t index)
    : bits_(&bits), index_(index) {}

std::bitset<8>::reference Byte::Iterator::operator*() const {
  if (index_ > 8) {
    throw std::out_of_range("Index out of range.");
  }
  return (*bits_)[index_];
}

std::bitset<8>::reference Byte::Iterator::operator*() {
  if (index_ > 8) {
    throw std::out_of_range("Index out of range.");
  }
  return (*bits_)[index_];
}

Byte::Iterator& Byte::Iterator::operator++() {
  --index_;
  return *this;
}

Byte::Iterator& Byte::Iterator::operator--() {
  ++index_;
  return *this;
}

bool Byte::Iterator::operator!=(const Byte::Iterator& other) const {
  return bits_ != other.bits_ || index_ != other.index_;
}

Byte::ReverseIterator::ReverseIterator(std::bitset<8>& bits, std::size_t index)
    : bits_(&bits), index_(index) {}

std::bitset<8>::reference Byte::ReverseIterator::operator*() const {
  if (index_ > 8) {
    throw std::out_of_range("Index out of range.");
  }
  return (*bits_)[index_];
}

std::bitset<8>::reference Byte::ReverseIterator::operator*() {
  if (index_ > 8) {
    throw std::out_of_range("Index out of range.");
  }
  return (*bits_)[index_];
}

Byte::ReverseIterator& Byte::ReverseIterator::operator++() {
  ++index_;
  return *this;
}

Byte::ReverseIterator& Byte::ReverseIterator::operator--() {
  --index_;
  return *this;
}

bool Byte::ReverseIterator::operator!=(
    const Byte::ReverseIterator& other) const {
  return bits_ != other.bits_ || index_ != other.index_;
}

Byte::Byte(const std::bitset<8>& byte): byte_(byte) {}

Byte::Byte(const std::uint8_t data): byte_(data) {}

Byte::Byte(const std::string& data, const Base& base) {
  WithinRange(data, base);
  int base_value = static_cast<int>(base);
  std::uint8_t bits = std::stoul(data, nullptr, base_value);
  byte_ = bits;
}

std::ostream& operator<<(std::ostream& stream, const Byte& data) {
  stream << data.GetByte();
  return stream;
}

std::ostream& operator<<(std::ostream& stream, 
                         const std::bitset<8>::reference bit) {
  stream << static_cast<bool>(bit);
  return stream;
}

Byte Byte::operator&(const Byte& data) const {
  return byte_ & data.byte_;
}

Byte& Byte::operator&=(const Byte& data) {
  byte_ &= data.byte_;
  return *this;
}

Byte Byte::operator|(const Byte& data) const {
  return byte_ | data.byte_;
}

Byte& Byte::operator|=(const Byte& data) {
  byte_ |= data.byte_;
  return *this;
}

Byte Byte::operator^(const Byte& data) const {
  return byte_ ^ data.byte_;
}

Byte& Byte::operator^=(const Byte& data) {
  byte_ ^= data.byte_;
  return *this;
}

Byte Byte::operator~() const {
  return std::bitset<8>(byte_).flip();
}

Byte Byte::operator<<(std::size_t n_pos) const {
  if (n_pos > 7) {
    throw std::runtime_error("Invalid shift count for byte.");
  }
  return byte_ << n_pos;
}

Byte Byte::operator>>(std::size_t n_pos) const {
  if (n_pos > 7) {
    throw std::runtime_error("Invalid shift count for byte.");
  }
  return byte_ >> n_pos;
}

Byte& Byte::operator<<=(std::size_t n_pos) {
  if (n_pos > 7) {
    throw std::runtime_error("Invalid shift count for byte.");
  }
  byte_ <<= n_pos;
  return *this;
}

Byte& Byte::operator>>=(std::size_t n_pos) {
  if (n_pos > 7) {
    throw std::runtime_error("Invalid shift count for byte.");
  }
  byte_ >>= n_pos;
  return *this;
}

Byte Byte::operator*(Byte byte2) const {
  Byte result(0x00);
  Byte byte1(byte_);
  while (byte2.IsAnySet()) {  // Equivalent with byte2.ToInt() > 0
    // Checks if LSB is set to `1`.
    if (byte2[0] == 1) {
      result ^= byte1;
    }
    byte2 >>= 1;
    // Checks if MSB is set to `1`.
    if (byte1[7] == 1) {
      byte1 <<= 1;
      // Reducing using the irreducible polynomial.
      byte1 ^= Byte(0x1b);
      continue;
    }
    byte1 <<= 1;
  }
  return result ;
}

bool Byte::operator[](std::size_t pos) const {
  if (pos > 7) {
    throw std::out_of_range("The bit from position " + std::to_string(pos) + 
                            " is out of range.");
  }
  return byte_[pos];
}

std::bitset<8>::reference Byte::operator[](std::size_t pos) {
  if (pos > 7) {
    throw std::out_of_range("The bit from position " + std::to_string(pos) + 
                            " is out of range.");
  }
  return byte_[pos];
}

bool Byte::operator==(const Byte& byte) const {
  return byte_ == byte.byte_;
}

bool Byte::operator!=(const Byte& byte) const {
  return byte_ != byte.byte_;
}

std::string Byte::ToHex() const {
  std::stringstream stream;
  stream << std::hex << std::setw(2) << std::setfill('0') << byte_.to_ulong();
  return stream.str();
}

void Byte::WithinRange(const std::string& data, const Base& base) const {
  int num_data = 0;
  switch (base) {
    case Base::base_2:
      if (data.length() > 8) {
        throw std::length_error("Given binary data is larger than expected.");
      }
      if (data.find_first_not_of("01") != std::string::npos) {
        throw std::invalid_argument("Expected only binary characters.");
      }
      break;
    case Base::base_10:
      if (!std::all_of(data.begin(), data.end(), ::isdigit)) {
        throw std::invalid_argument("Expected only numbers.");
      }
      num_data = std::stoi(data);
      if (num_data > 255) {
        throw std::length_error("Given decimal data is larger than expected.");
      }
      break;
    case Base::base_16:
      if (data.length() > 2) {
        throw std::length_error("Given hexadecimal data is larger than expected.");
      }
      if (!std::all_of(data.begin(), data.end(), ::isxdigit)) {
        throw std::invalid_argument("Expected only hexadecimal characters.");
      }
      break;
    default:
      throw std::runtime_error("Unexpected given base.");  
  }
}

}  // namespace ByteUtils