#pragma once

#include <string>
#include <cstdint>

#include "bitstring.h"

// Ketje Jr: keccak-pstar[200]
#define STATE_BYTES 25
#define STATE_BITS (STATE_BYTES*8)

class MonkeyDuplex{
  public:
    MonkeyDuplex(unsigned int r, unsigned int nstart, unsigned int nstep, unsigned int nstride);
    void start(BitString I);
    BitString step(BitString I, size_t extract_bits);
    BitString stride(BitString I, size_t extract_bits);
  private:
    uint8_t state[STATE_BYTES];
    unsigned int r;
    unsigned int nstart;
    unsigned int nstep;
    unsigned int nstride;
    BitString genericStep(BitString I, size_t extract_bits, unsigned int steps);
};
