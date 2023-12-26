#ifndef BYTE_UTILS_WORD_H_
#define BYTE_UTILS_WORD_H_

#include <cstdint>
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
    // The class `Iterator` provides a mechanism 
    // to traverse a `Word` instance.
    class Iterator {
      public:
        Iterator(std::vector<Byte>& word, std::size_t index)
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
        std::vector<Byte>* word_;
        std::size_t index_;
    };
    // The class `ConstIterator` provides a mechanism
    // to travers a `const Word` instance.
    class ConstIterator {
      public:
        ConstIterator(const std::vector<Byte>& word, std::size_t index)
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
        const std::vector<Byte>* word_;
        std::size_t index_;
    };
    // The class `ReverseIterator` provides a mechanism 
    // to traverse a `Word` instance in reverse order.
    class ReverseIterator {
      public:
        ReverseIterator(std::vector<Byte>& word, std::size_t index)
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
        std::vector<Byte>* word_;
        std::size_t index_;
    };
    // The class `ConstReverseIterator` provides a mechanism
    // to travers a `const Word` instance in reverse order.
    class ConstReverseIterator {
      public:
         ConstReverseIterator(const std::vector<Byte>& word, std::size_t index)
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
        const std::vector<Byte>* word_;
        std::size_t index_;
    };
    // Creates an empty `Word` object with `N` bits.
    Word(std::size_t bits = 32);
    // Creates a dynamic sized `Word` object with given hexadecimal values.
    Word(const std::string& hex_string, const std::size_t bits = 32);
    // Creates a dynamic sized `Word` object with given decimal value
    Word(std::int64_t decimal_value, std::size_t bits = 32);
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
    Iterator begin() { return Iterator(word_, 0); }
    // Returns the `ConstIterator` that points to the first `Byte` 
    // from the `const Word`.
    ConstIterator begin() const { return ConstIterator(word_, 0); }
    // Returns the `ReverseIterator` that points to the last 
    // `Byte` from the `Word`.
    ReverseIterator rbegin() { return ReverseIterator(word_, word_.size()-1); }
    // Returns the `ConstReverseIterator` that points to the last 
    // `Byte` from the `const Word`.
    ConstReverseIterator rbegin() const { 
      return ConstReverseIterator(word_, word_.size()-1); 
    }
    // Returns the `Iterator` that points to the last `Byte` from the `Word`.
    Iterator end() { return Iterator(word_, word_.size()); }
    // Returns the `ConstIterator` that points to the last `Byte`
    //  from the `const Word`.
    ConstIterator end() const { return ConstIterator(word_, word_.size()); }
    // Returns the `ReverseIterator` that points to the first 
    // `Byte` from the `cons Word`.
    ReverseIterator rend() { return ReverseIterator(word_, -1); }
    // Returns the `ConstReverseIterator` that points to the first 
    // `Byte` from the `const Word`.
    ConstReverseIterator rend() const { 
      return ConstReverseIterator(word_, -1); 
    }
    // Performs the XOR operation between two `Word` objects.
    Word operator^(const Word& word) const;
    // Performs the XOR operation between `Word` and `Byte` objects.
    Word operator^(const Byte& byte) const;
    // Performs the AND operation between two `Word` objects.
    Word operator&(const Word& word) const; 
    // Performs the OR operation between two `Word` objects.
    Word operator|(const Word& word) const;
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
    // Pushes back a `Byte` object.
    void PushBack(const Byte& byte);
    std::string ToHex() const;
    // Returns the size of `Word` object in bytes.
    inline const std::size_t Size() const { return word_.size(); }
    inline const std::vector<Byte> GetWord() const { return word_; }
  private:
    std::vector<Byte> word_;
};

}  // namespace ByteUtils

#endif  // BYTE_UTILS_WORD_H_