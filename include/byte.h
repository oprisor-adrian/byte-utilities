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
#ifndef BYTE_UITILS_BYTE_H_
#define BYTE_UITILS_BYTE_H_

#include <bitset>
#include <cstdint>
#include <ostream>
#include <string>

namespace ByteUtils {

// Defines different numerical bases.
enum class Base {
  base_2 = 2,
  base_10 = 10,
  base_16 = 16,
};

// The `Byte` class manage and performs bitwise operations on 
// an array of 8 bits. The class do not handle representation
// of negative values. The bits are formatted in little-endian order.
// Example:
//     ByteUtils::Byte byte1(0x57);
//     ByteUtils::Byte byte2("11101101", ByteUtils::Base:base_2);
//     std::cout << (byte1 * byte2);
class Byte {
  public:
    // The class `Iterator` provides a mechanism 
    // to traverse a `Byte` instance from LSB to MSB.
    class Iterator {
      public:
        Iterator(std::bitset<8>& bits, std::size_t index);
        // Returns a constant reference to the bit from position `index_`. 
        std::bitset<8>::reference operator*() const;
        // Returns a reference to the bit from position `index_`.
        std::bitset<8>::reference operator*();
        // Moves the index towards the MSB.
        Iterator& operator++();
        // Moves the index towards the LSB.
        Iterator& operator--();
        bool operator!=(const Iterator& other) const;
      private:
        std::bitset<8>* bits_;
        std::size_t index_;
    };
    // The class `ReverseIterator` provides a mechanism 
    // to traverse a `Byte` instance from MSB to LSB.
    class ReverseIterator {
      public:
        ReverseIterator(std::bitset<8>& bits, std::size_t index);
        // Returns a constant reference to the bit from position `index_`.
        std::bitset<8>::reference operator*() const;
        // Returns a reference to the bit from position `index_`.
        std::bitset<8>::reference operator*();
        // Moves the index towards the MSB.
        ReverseIterator& operator++();
        // Moves the index towards the LSB.
        ReverseIterator& operator--();
        bool operator!=(const ReverseIterator& other) const;
      private:
        std::bitset<8>* bits_;
        std::size_t index_;
    };
    Byte() = default;
    // Creates a `Byte` from `std::bitset<8>`.
    Byte(const std::bitset<8>& byte);
    // Creates a `Byte` object that represents 8 bits of `unsigned data`.
    Byte(const std::uint8_t data);
    // Creates a `Byte` object from input data formatted in big-endian order.
    Byte(const std::string& data, const Base& base);
    Byte(const Byte& other) = default;
    Byte(Byte&& other) = default;
    Byte& operator=(const Byte& other) = default;
    Byte& operator=(Byte&& other) = default;
    ~Byte() = default;
    // Prints the `Byte` object as an array of bits formatted 
    // in big-endian order.
    friend std::ostream& operator<<(std::ostream& stream, const Byte& data);
    // Prints the reference to a bit.
    friend std::ostream& operator<<(std::ostream& stream,
                                    const std::bitset<8>::reference bit);
    // Returns a reference to the LSB.
    Iterator begin() { return Iterator(byte_, 7); }
    // Returns a reference to the MSB.
    ReverseIterator rbegin() { return ReverseIterator(byte_, 0); }
    // Returns a reference to the MSB.
    Iterator end() { return Iterator(byte_, -1); }
    // Returns a reference to the LSB.
    ReverseIterator rend() { return ReverseIterator(byte_, 8); }
    // Performs bitwise AND operation between two `Byte` objects.
    Byte operator&(const Byte& data) const;
    // Performs bitwise AND operation on current `Byte` object.
    Byte& operator&=(const Byte& data);
    // Performs bitwise OR operation between two `Byte` objects.
    Byte operator|(const Byte& data) const;
    // Performs bitwise OR operations on current `Byte` obect.
    Byte& operator|=(const Byte& data);
    // Performs bitwise XOR operation between two `Byte` objects.
    Byte operator^(const Byte& data) const;
    // Performs bitwise XOR on current `Byte` object.
    Byte& operator^=(const Byte& data);
    // Returns the complement of the current `Byte` object.
    Byte operator~() const;
    // Performs left shift with `n_pos` positions.
    Byte operator<<(std::size_t n_pos) const;
    // Performs right shift with `n_pos` positions.
    Byte operator>>(std::size_t n_pos) const;
    // Performs left shift on current `Byte` object with `n_pos` positions.
    Byte& operator<<=(std::size_t n_pos);
    // Performs right shift on current `Byte` object with `n_pos` positions.
    Byte& operator>>=(std::size_t n_pos);
    // Performs Galois Field multiplication between two `Byte` objects.
    Byte operator*(Byte byte) const;
    // Returns the bit from the position `pos`.
    bool operator[](std::size_t pos) const;
    // Accesses the bit from the position `pos`.
    std::bitset<8>::reference operator[](std::size_t pos);
    // Checks if two `Byte` objects are equal.
    bool operator==(const Byte& byte) const;
    // Checks if two `Byte` objects are not equal.
    bool operator!=(const Byte& byte) const;
    // Checks if at least one bit is set to `1`.
    inline bool IsAnySet() const { return byte_.any(); }
    inline int ToInt() const { return byte_.to_ulong(); }
    std::string ToHex() const;
    inline const std::bitset<8>& GetByte() const { return byte_; }
  private:
    // Checks the validity of the input `data`.
    void WithinRange(const std::string& data, const Base& base) const;
    std::bitset<8> byte_;
};

}  // namespace ByteUtils

#endif  // BYTE_UITILS_BYTE_H_