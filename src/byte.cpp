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
#include "byte.h"

#include <iomanip>
#include <exception>
#include <sstream>

namespace ByteUtils {

Byte::Byte(const std::bitset<8>& byte): byte_(byte) {}

Byte::Byte(const std::uint8_t data): byte_(data) {}

Byte::Byte(const std::string& data, const uint8_t base) {
  if (base != 2 && base != 16) {
    throw std::invalid_argument("Representation can be made only for binary "
                                "or hexadecimal values.");
  }
  if (base == 16 && data.size() > 2) {
    throw std::invalid_argument("Given hexadecimal data can't be represented " 
                                "in 1 byte.");
  }
  if (base == 2 && data.size() > 8) {
    throw std::invalid_argument("Given binary data can't be represented " 
                                "in 1 byte.");
  }
  std::uint8_t bits = std::stoul(data, nullptr, base);
  byte_ = bits;
}

std::ostream& operator<<(std::ostream& stream, const Byte& data) {
  stream << data.byte_;
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const std::bitset<8>::reference bit) {
  stream << static_cast<bool>(bit);
  return stream;
}

Byte Byte::operator&(const Byte& data) const {
  return byte_ & data.byte_;
}

Byte Byte::operator|(const Byte& data) const {
  return byte_ | data.byte_;
}

Byte Byte::operator^(const Byte& data) const {
  return byte_ ^ data.byte_;
}

Byte& Byte::operator^=(const Byte& data) {
  byte_ ^= data.byte_;
  return *this;
}

Byte Byte::operator~() const {
  return ~byte_;
}

Byte Byte::operator<<(const std::size_t n_pos) const {
  return byte_ << n_pos;
}

Byte& Byte::operator<<=(const std::size_t n_pos) {
  byte_ <<= n_pos;
  return *this;
}

Byte& Byte::operator>>=(const std::size_t n_pos) {
  byte_ >>= n_pos;
  return *this;
}

Byte Byte::operator*(const Byte& byte) const {
  Byte result;
  Byte byte1(byte_);
  Byte byte2(byte);
  while (byte2.IsAnySet()) {
    // Checks if LSB is set to `1`.
    if (byte2[0] == true) {
      result ^= byte1;
    }
    byte2 >>= 1;
    // Checks if MSB is set to `1`.
    if (byte1[7] == true) {
      byte1 <<= 1;
      // Reducing using the irreducible polynomial.
      byte1 ^= 0x1b;
      continue;
    }
    byte1 <<= 1;
  }
  return result ;
}

bool Byte::operator[](const std::size_t pos) const {
  if (pos > 7) {
    throw std::out_of_range("The bit from position " + std::to_string(pos) + 
                            " is out of range.");
  }
  return byte_[pos];
}

std::bitset<8>::reference Byte::operator[](const std::size_t pos) {
  if (pos > 7) {
    throw std::out_of_range("The bit from position " + std::to_string(pos) + 
                            " is out of range.");
  }
  return byte_[pos];
}

std::string Byte::ToHex() const {
  std::stringstream stream;
  stream << std::hex << std::setw(2) << std::setfill('0') << byte_.to_ulong();
  return stream.str();
}

}  // namespace ByteUtils