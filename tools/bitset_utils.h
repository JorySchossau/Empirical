// This file is part of Empirical, https://github.com/mercere99/Empirical/, and is 
// Copyright (C) Michigan State University, 2015. It is licensed 
// under the MIT Software license; see doc/LICENSE

#ifndef EMP_BITSET_UTILS_H
#define EMP_BITSET_UTILS_H

//////////////////////////////////////////////////////////////////////////////
//
//  This file contains a set of simple functions to manipulate bitsets.
//

#include "functions.h"

namespace emp {

  template <int NUM_BITS>
  constexpr uint32_t UIntMaskFirst() { return (UIntMaskFirst<NUM_BITS-1> << 1) | 1; }

  template <>
  constexpr uint32_t UIntMaskFirst<0>() { return 0; }

  // Dealing with bits in uint64_t variables
  const int ByteCount[256] = {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
  };

  inline int count_bits(uint64_t val) {
    return
      ByteCount[  val >> 56         ] +
      ByteCount[ (val >> 48) & 0xFF ] +
      ByteCount[ (val >> 40) & 0xFF ] +
      ByteCount[ (val >> 32) & 0xFF ] +
      ByteCount[ (val >> 24) & 0xFF ] +
      ByteCount[ (val >> 16) & 0xFF ] +
      ByteCount[ (val >>  8) & 0xFF ] +
      ByteCount[  val        & 0xFF ];
  }

  inline int count_bits(uint32_t val) {
    return 
      ByteCount[  val >> 24         ] +
      ByteCount[ (val >> 16) & 0xFF ] +
      ByteCount[ (val >>  8) & 0xFF ] +
      ByteCount[  val        & 0xFF ];
  }

  inline int find_bit(uint64_t val) { return count_bits( (~val) & (val-1) ); }
  inline int find_bit(const uint32_t val) { return count_bits( (~val) & (val-1) ); }

  /*
  // Returns the position of the first set (one) bit or a -1 if none exist.
  template <size_t BITS>
  int find_bit(const std::bitset<BITS> & in) {
    int offset = 0;
    uint64_t tmp_bits = 0ULL;
    while (offset < BITS && ((tmp_bits = (in >> offset).to_ullong()) == 0ULL)) {
      offset += 64;
    }
    return tmp_bits ? find_bit(tmp_bits) + offset : -1;
  }

  template <size_t BITS1, size_t BITS2>
  std::bitset<BITS1+BITS2> concat_bits(std::bitset<BITS1> in1, std::bitset<BITS2> in2) {
    constexpr int BITS_OUT = BITS1 + BITS2;  // How many bits are in the output?
    constexpr int FULL_ULLS1 = BITS1 >> 6;   // How many 64-bit groups of bits fit into in1?
    constexpr int FULL_ULLS2 = BITS2 >> 6;   // How many 64-bit groups of bits fit into in2?
    // constexpr int EXTRA_BITS1 = BITS1 & 63;  // How many bits are leftover in BITS1?
    constexpr int EXTRA_BITS2 = BITS2 & 63;  // How many bits are leftover in BITS2?
    std::bitset<BITS_OUT> out_bits;

    // Copy over in1...
    for (int i = FULL_ULLS1; i >= 0; --i) {
      out_bits <<= 64;                          // Make room for the next group of bits.
      out_bits |= (in1 >> (i*64)).to_ullong();  // Put them in place.
    }
  }

  template <size_t BITS>
  constexpr std::bitset<BITS> mask_bit(uint32_t id) {
    return (std::bitset<BITS>(1)) << id;
  }

  template <size_t BITS>
  constexpr std::bitset<BITS> mask_pattern(size_t start, size_t step, size_t end) {
    return mask_bit<BITS>(start) | std::bitset<BITS>(mask_pattern<BITS*(start<end)>(start+step,step,end));
  }

  template <>
  constexpr size_t mask_pattern<0>(size_t start, size_t step, size_t end) {
    return 0;
  }
  */
}

#endif
