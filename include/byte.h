#ifndef BYTE_UITILS_BYTE_H_
#define BYTE_UITILS_BYTE_H_

#include <bitset>
#include <cstdint>
#include <ostream>
#include <string>

namespace ByteUtils {

// The `Byte` class manage and performs bitwise operations on 
// an array of 8 bits. The bit positioned at the far left signifies 
// the MSB, while the bit at the far right signifies LSB.
// Example:
//     ByteUtils::Byte byte1(0x57);
//     ByteUtils::Byte byte2("83", 16);
//     ByteUtils::Byte result = byte1 * byte2;
//     std::cout << result;
class Byte {
  public:
    // The class `Iterator` class provides a mechanism 
    // to traverse a `Byte` instance.
    class Iterator {
      public:
        Iterator(std::bitset<8>& bits, const std::size_t index)
            : bits_(&bits), index_(index) {}
        // Returns a constant reference to the bit from position `index_`. 
        inline std::bitset<8>::reference operator*() const { 
          return (*bits_)[index_]; 
        }
        // Returns a reference to the bit from position `index_`.
        inline std::bitset<8>::reference operator*() { 
          return (*bits_)[index_]; 
        }
        // Moves the index towards the LSB.
        Iterator& operator++() { ++index_; return *this; }
        // Moves the index towards the MSB.
        Iterator& operator--() { --index_; return *this; }
        bool operator!=(const Iterator& other) const { 
          return bits_ != other.bits_ || index_ != other.index_; 
        }
      private:
        std::bitset<8>* bits_;
        std::size_t index_;
    };
    // The class `ReverseIterator` class provides a mechanism 
    // to traverse a `Byte` instance in reverse order.
    class ReverseIterator {
      public:
        ReverseIterator(std::bitset<8>& bits, std::size_t index)
            : bits_(&bits), index_(index) {}
        // Returns a constant reference to the bit from position `index_`.
        inline std::bitset<8>::reference operator*() const {
          return (*bits_)[index_];
        }
        // Returns a reference to the bit from position `index_`.
        inline std::bitset<8>::reference operator*() {
          return (*bits_)[index_];
        }
        // Moves the index towards the MSB.
        ReverseIterator& operator++() { --index_; return *this; }
        // Moves the index towards the LSB.
        ReverseIterator& operator--() { ++index_; return *this; }
        bool operator!=(const ReverseIterator& other) const { 
          return bits_ != other.bits_ || index_ != other.index_; 
        }
      private:
        std::bitset<8>* bits_;
        std::size_t index_;
    };
    Byte() = default;
    // Initializes the `Byte` object with 8 bits of data.
    Byte(const std::bitset<8>& byte);
    // Initializes the `Byte` object with 8 bits of data.
    Byte(const std::uint8_t data);
    // Initializes the `Byte` object with exact 8 bits of `data`
    // in given `base`, where `base` can be 2 or 16.
    Byte(const std::string& data, const uint8_t base);
    Byte(const Byte& other) = default;
    Byte(Byte&& other) = default;
    Byte& operator=(const Byte& other) = default;
    Byte& operator=(Byte&& other) = default;
    ~Byte() = default;
    // Prints the `Byte` object as an array of bits from the MSB to LSB.
    friend std::ostream& operator<<(std::ostream& stream, const Byte& data);
    // Prints the reference to a bit as bool value.
    friend std::ostream& operator<<(std::ostream& stream,
                                    const std::bitset<8>::reference bit);
    // Returns a reference to the MSB.
    Iterator begin() { return Iterator(byte_, 0); }
    // Returns a reference to the LSB.
    ReverseIterator rbegin() { return ReverseIterator(byte_, 7); }
    // Returns a reference to the LSB.
    Iterator end() { return Iterator(byte_, 8); }
    // Returns a reference to the MSB.
    ReverseIterator rend() { return ReverseIterator(byte_, -1); }
    // Performs bitwise `AND` operation between two `Byte` objects.
    Byte operator&(const Byte& data) const;
    // Performs bitwise `OR` operation between two `Byte` objects.
    Byte operator|(const Byte& data) const;
    // Performs bitwise `XOR` operation between two `Byte` objects.
    Byte operator^(const Byte& data) const;
    // Performs bitwise `XOR` on current `Byte` object.
    Byte& operator^=(const Byte& data);
    // Returns the complement of the current `Byte` object.
    Byte operator~() const;
    // Performs left shift with `n_pos` positions.
    Byte operator<<(const std::size_t n_pos) const;
    // Performs left shift on current `Byte` object with `n_pos` positions.
    Byte& operator<<=(const std::size_t n_pos);
    // Performs right shift on current `Byte` object with `n_pos` positions.
    Byte& operator>>=(const std::size_t n_pos);
    // Performs Galois Field multiplication between two `Byte` objects.
    Byte operator*(const Byte& byte) const;
    // Returns the bit from the position `pos`.
    bool operator[](const std::size_t pos) const;
    // Accesses the bit from the position `pos` through 
    // `std::bitset::reference`.
    std::bitset<8>::reference operator[](const std::size_t pos);
    // Checks if at least one bit is set to `1`.
    inline bool IsAnySet() const { return byte_.any(); }
    inline int ToInt() const { return byte_.to_ulong(); }
    inline char ToAscii() const { return byte_.to_ulong(); }
    std::string ToHex() const;
    inline const std::bitset<8>& GetByte() const { return byte_; }
  private:
    std::bitset<8> byte_;
};

}  // namespace ByteUtils

#endif  // BYTE_UITILS_BYTE_H_