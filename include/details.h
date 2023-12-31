#ifndef BYTE_UTILS_DETAILS_H_
#define BYTE_UTILS_DETAILS_H_

#include "word.h"

namespace ByteUtils::details {

template<std::size_t bits>
struct WordWrapper {
  Word<bits> word_;
  WordWrapper(Word<bits> word) : word_(word) {}
};

}  // namespace details

#endif  // BYTE_UTILS_DETAILS_H_