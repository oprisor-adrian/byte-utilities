#ifndef BYTE_UTILS_BYTE_VECTOR_H_
#define BYTE_UTILS_BYTE_VECTOR_H_

#include <ostream>
#include <string>
#include <vector>

#include "byte.h"

namespace ByteUtils {

class Word;

// The `ByteVector` class manage a vector of `N` `Byte` objects. 
// Example:
//    ByteUtils::ByteVector bytes("0a1b");
//    std::cout << bytes[0];
class ByteVector{
  public:
    // The class `Iterator` class provides a mechanism 
    // to traverse a `ByteVector` instance.
    class Iterator {
      public:
        Iterator(std::vector<Byte>& bytes, std::size_t index)
            : bytes_(&bytes), index_(index) {}
        // Moves the index towards LSB. 
        inline Iterator& operator++() { ++index_; return *this; }
        // Moves the index towards MSB.
        inline Iterator& operator--() { --index_; return *this; }
        // Returns a reference to a `Byte~ from the `ByteVector` object.
        inline Byte& operator*() { return (*bytes_)[index_]; }
        // Returns a pointer to a `Byte` from `ByteVector` object.
        inline Byte* operator->() { return &(*bytes_)[index_]; }
        inline bool operator!=(const Iterator& other) const { 
          return bytes_ != other.bytes_ || index_ != other.index_; 
        }
      private:
        std::vector<Byte>* bytes_;
        std::size_t index_;
    };
    // The class `ReverseIterator` class provides a mechanism 
    // to traverse a `ByteVector` instance in reverse order.
    class ReverseIterator {
      public:
        ReverseIterator(std::vector<Byte>& bytes, const std::size_t index)
            : bytes_(&bytes), index_(index) {}
        // Moves the index towards MSB. 
        inline ReverseIterator& operator++() { --index_; return *this; }
        // Moves the index towards LSB.
        inline ReverseIterator& operator--() { ++index_; return *this; }
        // Returns a reference to a byte from the `Word` object.
        inline Byte& operator*() { return (*bytes_)[index_]; }
        // Returns a pointer to a `Byte` from `ByteVector` object.
        inline Byte* operator->() { return &(*bytes_)[index_]; }
        inline bool operator!=(const ReverseIterator& other) const {
          return bytes_ != other.bytes_ || index_ != other.index_; 
        }
      private:
        std::vector<Byte>* bytes_;
        std::size_t index_;
    };
    ByteVector() = default;
    // Initializes the `ByteVector` object with a string of hexadecimal values.
    ByteVector(const std::string& hex_string);
    // Initializes the `ByteVector` object with a vector of `Byte` objects.
    ByteVector(const std::vector<Byte>& bytes);
    ByteVector(const ByteVector& other) = default;
    ByteVector(ByteVector&& other) = default;
    ByteVector& operator=(const ByteVector& other) = default;
    ByteVector& operator=(ByteVector&& other) = default;
    ~ByteVector() = default;
    // Prints the `ByteVector` objects as an array of bits.
    friend std::ostream& operator<<(std::ostream& stream, 
                                    const ByteVector& bytes);
    // Returns the `Iterator` that points to the first `Byte` 
    // from the `ByteVector`.
    Iterator begin() { return Iterator(bytes_, 0); }
    // Returns the `ReverseIterator` that points to the last 
    // `Byte` from the `ByteVector`.
    ReverseIterator rbegin() { return ReverseIterator(bytes_, bytes_.size()-1); }
    // Returns the `Iterator` that points to the last `Byte` 
    // from the `ByteVector`.
    Iterator end() { return Iterator(bytes_, bytes_.size()); }
    // Returns the `ReverseIterator` that points to the first 
    // `Byte` from the `ByteVector`.
    ReverseIterator rend() { return ReverseIterator(bytes_, -1); }
    // Returns the `Byte` from the position `pos`.
    Byte operator[](const std::size_t pos) const;
    // Accesses the `Byte` from the position `pos`.
    Byte& operator[](const std::size_t pos);
    // Pushes back the bytes from the `Word` object.
    void PushBack(const Word& word);
    // Returns the `Word` object from the position `pos`.
    Word GetWord(const std::size_t pos) const;
    // Returns a vector of size `count` by 'Word' objects.
    std::vector<Word> GetWord(const std::size_t pos, 
                              const std::size_t count) const;
    std::string ToHex() const;
    // Returns the number of bytes from the `ByteVector` object.
    inline std::size_t Size() const { return bytes_.size(); }
  private:
    std::vector<Byte> bytes_;
};

}  // namespace ByteUtils

#endif  // BYTE_UTILS_BYTE_VECTOR_H_