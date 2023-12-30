#include <assert.h>
#include <iostream>
#include <cstring>

#include "monkeyduplex.hpp"
#include "utils.hpp"

#include "Keccak-f.h"

MonkeyDuplex::MonkeyDuplex(unsigned int r, unsigned int nstart, unsigned int nstep, unsigned int nstride)
      : r(r),
        nstart(nstart),
        nstep(nstep),
        nstride(nstride){
    assert(nstep < nstride);
    assert(r < STATE_BYTES);
};

void MonkeyDuplex::start(BitString I){
    assert(I.size() <= STATE_BITS-2);
    //std::cout << "start I " << I << std::endl;

    I = I || BitString::pad101(STATE_BITS, I.size());
    //std::cout << "start I padded " << I << std::endl;
    memcpy(state, I.array(), STATE_BYTES);

    //std::cout << "start state " << format_hex(state, STATE_BYTES) << std::endl;

    KeccakPStar(200,nstart)(state);
    //std::cout << "start permuted state " << format_hex(state, STATE_BYTES) << std::endl;
}

BitString MonkeyDuplex::step(BitString I, size_t extract_bits){
    assert(I.size() <= r-2);
    assert(extract_bits <= r);

    //std::cout << "step I " << I << std::endl;
    I = I || BitString::pad101(r, I.size());
    //std::cout << "step padded I" << I << std::endl;

    I = I || BitString::zeroes(STATE_BITS - r);
    const uint8_t *s = I.array();
    for(int i=0; i<STATE_BYTES; i++){
        state[i] ^= s[i];
    }
    //std::cout << "step state XOR " << format_hex(state, STATE_BYTES) << std::endl;

    KeccakPStar(200,nstep)(state);
    return BitString(state, extract_bits);
}

