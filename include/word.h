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
// exact 32 bits of data, treated as a single entity.
// Example:
//    ByteUtils::Word word1("ffffffff");
//    ByteUtils::Word word2("0a0a0a0a");
//    ByteUtils::Word result = word1 ^ word2;
//    std::cout << result;
class Word {
  public:
    Word() = default;
    // Initializes the `Word` object with 32 bits hexadecimal value.
    Word(const std::string& data);
    // Initializes the `Word` object with an array of 4 `Byte` objects.
    Word(const std::vector<Byte>& word);
    Word(const Word& other) = default;
    Word(Word&& other) = default;
    Word& operator=(const Word& other) = default;
    Word& operator=(Word&& other) = default;
    ~Word() = default;
    // Prints the `Word` object as an array of bits.
    friend std::ostream& operator<<(std::ostream& stream, const Word& data);
    // Performs the XOR operation between two `Word` objects.
    Word operator^(const Word& word) const;
    // Performs the XOR operation between `Word` and `Byte` objects.
    Word operator^(const Byte& byte) const;
    // Returns a byte from position `pos`.
    Byte operator[](const std::size_t pos) const;
    // Accesses the byte from the position `pos`.
    Byte& operator[](const std::size_t pos);
    std::string ToHex() const;
    inline const std::vector<Byte>& GetWord() const { return word_; }
  private:
    std::vector<Byte> word_;
};

}  // namespace ByteUtils

#endif  // BYTE_UTILS_WORD_H_