#ifndef BYTE_UTILS_WORD_H_
#define BYTE_UTILS_WORD_H_

#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "byte.h"

namespace ByteUtils {

// The `Word` class manage and performs bitwise operations on 
// 'N' bits of data, treated as a single entity. The rightmost bit 
// represents the LSB and the leftmost bit represents the MSB. 
// Example:
//    ByteUtils::Word word1("ffffffff");
//    ByteUtils::Word word2("0a0a0a0a");
//    ByteUtils::Word result = word1 ^ word2;
//    std::cout << result;
class Word {
  public:
    // The class `Iterator` provides a way to travers the word 
    // from the MSB to the LSB.
    class Iterator {
      public:
        Iterator(std::vector<Byte>::iterator iterator)
            : iterator_(iterator) {}
        // Move the index towards LSB. 
        inline Iterator& operator++() { ++iterator_; return *this; }
        // Move the index towards MSB.
        inline Iterator& operator--() { --iterator_; return *this; }
        // Returns a constant reference to a byte from `Word` object.
        inline Byte operator*() const { return *iterator_; }
        // Returns a reference to a byte from the `Word` object.
        inline Byte& operator*() { return *iterator_; }
        inline bool operator!=(const Iterator& other) const { 
          return iterator_ != other.iterator_; 
        }
      private:
        std::vector<Byte>::iterator iterator_;
    };
    Word() = default;
    // Creates a dynamic size `Word` object with given hexadecimal values.
    Word(const std::string& hex_string, const std::size_t bits = 32);
    // Initializes the `Word` object with an array of `Byte` objects.
    Word(const std::vector<Byte>& word);
    Word(const Word& other) = default;
    Word(Word&& other) = default;
    Word& operator=(const Word& other) = default;
    Word& operator=(Word&& other) = default;
    ~Word() = default;
    // Prints the `Word` object as an array of bits.
    friend std::ostream& operator<<(std::ostream& stream, const Word& data);
    // Returns the `Iterator` that points to the first `Byte` from the `Word`.
    Iterator begin() { return Iterator(word_.begin()); }
    // Returns the `Iterator` that points to the last `Byte` from the `Word`.
    Iterator rbegin() { return Iterator(word_.end()); }
    // Returns the `Iterator` that points to the last `Byte` from the `Word`.
    Iterator end() { return Iterator(word_.end()); }
    // Returns the `Iterator` that pints to the first `Byte` from the `Word`.
    Iterator rend() { return Iterator(word_.begin()); }
    // Performs the XOR operation between two `Word` objects.
    Word operator^(const Word& word) const;
    // Performs the XOR operation between `Word` and `Byte` objects.
    Word operator^(const Byte& byte) const;
    // Performs the AND operation between two `Word` objects.
    Word operator&(const Word& word) const; 
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
    inline const std::size_t Size() const { return word_.size(); }
    inline const std::vector<Byte> GetWord() const { return word_; }
  private:
    std::vector<Byte> word_;
};

}  // namespace ByteUtils

#endif  // BYTE_UTILS_WORD_H_