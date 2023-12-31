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
#ifndef BYTE_UTILS_BYTE_VECTOR_H_
#define BYTE_UTILS_BYTE_VECTOR_H_

#include <ostream>
#include <string>
#include <vector>

#include "byte.h"
#include "details.h"
#include "word.h"

namespace ByteUtils {

// The `ByteVector` class manage a vector of `N` `Byte` objects. 
// Example:
//    ByteUtils::ByteVector bytes("0a1b");
//    std::cout << bytes[0];
class ByteVector{
  public:
    // The class `Iterator` provides a mechanism 
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
    // The class `ConstIterator` provides a mechanism 
    // to travers a `const ByteVector` instance.
    class ConstIterator {
      public:
        ConstIterator(const std::vector<Byte>& bytes, std::size_t index)
            : bytes_(&bytes), index_(index) {}
        // Moves the index towards LSB. 
        inline ConstIterator& operator++() { ++index_; return *this; }
        // Moves the index towards MSB.
        inline ConstIterator& operator--() { --index_; return *this; }
        // Returns a reference to a `Byte~ from the `ByteVector` object.
        inline const Byte& operator*() const { return (*bytes_)[index_]; }
        // Returns a pointer to a `Byte` from `ByteVector` object.
        inline const Byte* operator->() const { return &(*bytes_)[index_]; }
        inline bool operator!=(const ConstIterator& other) const { 
          return bytes_ != other.bytes_ || index_ != other.index_; 
        }
      private:
        const std::vector<Byte>* bytes_;
        std::size_t index_;
    };
    // The class `ReverseIterator` provides a mechanism 
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
    // The class `ConstReverseIterator` provides a mechanism
    // to travers a `const ByteVector` instance in reverse order.
    class ConstReverseIterator {
      public:
        ConstReverseIterator(const std::vector<Byte>& bytes, std::size_t index)
            : bytes_(&bytes), index_(index) {}
         // Moves the index towards MSB. 
        inline ConstReverseIterator& operator++() { --index_; return *this; }
        // Moves the index towards LSB.
        inline ConstReverseIterator& operator--() { ++index_; return *this; }
        // Returns a reference to a byte from the `Word` object.
        inline const Byte& operator*() const { return (*bytes_)[index_]; }
        // Returns a pointer to a `Byte` from `ByteVector` object.
        inline const Byte* operator->() const { return &(*bytes_)[index_]; }
        inline bool operator!=(const ConstReverseIterator& other) const {
          return bytes_ != other.bytes_ || index_ != other.index_; 
        }
      private:
        const std::vector<Byte>* bytes_;
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
    // Returns the `ConstIterator` that poinst to the first `Byte`
    // from the `const ByteVector`
    ConstIterator begin() const { return ConstIterator(bytes_, 0); }
    // Returns the `ReverseIterator` that points to the last 
    // `Byte` from the `ByteVector`.
    ReverseIterator rbegin() { return ReverseIterator(bytes_, bytes_.size()-1); }
    // Returns the `ConstReverseIterator` that points to the last
    // `Byte` from the `const ByteVector`.
    ConstReverseIterator rbegin() const { 
      return ConstReverseIterator(bytes_, bytes_.size()-1); 
    }
    // Returns the `Iterator` that points to the last `Byte` 
    // from the `ByteVector`.
    Iterator end() { return Iterator(bytes_, bytes_.size()); }
    // Returns the `ConstIterator` that points to the last `Byte`
    // from the `const ByteVector`.
    ConstIterator end() const { return ConstIterator(bytes_, bytes_.size()); }
    // Returns the `ReverseIterator` that points to the first 
    // `Byte` from the `ByteVector`.
    ReverseIterator rend() { return ReverseIterator(bytes_, -1); }
    // Returns the `ConstReverseIterator` that points to the first
    // `Byte` from the `const ByteVector`.
    ConstReverseIterator rend() const { 
      return ConstReverseIterator(bytes_, -1);
    }
    // Returns the `Byte` from the position `pos`.
    Byte operator[](std::size_t pos) const;
    // Accesses the `Byte` from the position `pos`.
    Byte& operator[](std::size_t pos);
    // Pushes back the bytes from the `Word` object.
    template<std::size_t bits>
    void PushBack(const Word<bits>& word);
    // Pushes back a `Byte` object.
    void PushBack(const Byte& byte);
    // Returns a `N` bits size `Word` object from the position `pos`.
    template<std::size_t bits>
    Word<bits> GetWord(std::size_t pos) const;
    // Returns a vector of size `count` of 'Word' objects.
    template<std::size_t bits>
    std::vector<Word<bits>> GetWord(std::size_t pos, std::size_t count) const;
    std::string ToHex() const;
    // Returns the number of bytes from the `ByteVector` object.
    inline std::size_t Size() const { return bytes_.size(); }
  private:
    std::vector<Byte> bytes_;
};

template<std::size_t bits>
void ByteVector::PushBack(const Word<bits>& word) {
  for (const auto& byte : word) {
    bytes_.push_back(byte);
  }
}

template<std::size_t bits>
Word<bits> ByteVector::GetWord(std::size_t pos) const {
  if (pos >= bytes_.size()/4) {
    throw std::out_of_range("The position `pos` is out of range.");
  }
  Word<bits> word;
  std::size_t bytes_2_get = RoundUp(bits);
  auto begin = bytes_.begin()+pos*4;
  auto end = bytes_.begin()+pos*4+4;
  std::size_t index = 0;
  for (auto byte = begin; byte != end; ++byte) {
    word[index++] = *byte;
  }
  return word;
}

template<std::size_t bits>
std::vector<Word<bits>> ByteVector::GetWord(std::size_t pos, 
                                           std::size_t count) const {
  std::vector<Word<bits>> words;
  for (std::size_t index = 0; index < count; index++) {
    words.emplace_back(GetWord<bits>(pos+index));
  }
  return words;
}

}  // namespace ByteUtils

#endif  // BYTE_UTILS_BYTE_VECTOR_H_