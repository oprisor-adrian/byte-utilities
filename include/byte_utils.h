#ifndef BYTE_UTILS_BYTE_UTILS_H_
#define BYTE_UTILS_BYTE_UTILS_H_

#include <cstdint>

namespace ByteUtils::detail {

// Rounds up to nearest byte.
constexpr std::size_t RoundUp(std::size_t bits) {
  return (bits + 7) / 8;
}

}  // namespace detail

#endif  // BYTE_UTILS_BYTE_UTILS_H_