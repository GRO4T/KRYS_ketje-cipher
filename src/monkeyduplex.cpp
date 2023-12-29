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
    //std::cout << I << std::endl;

    I = I || BitString::pad101(STATE_BITS, I.size());
    //std::cout << I << std::endl;
    memcpy(state, I.array(), STATE_BYTES);

    KeccakPStar(200,nstart)(state);
    //std::cout << format_hex(state, STATE_BYTES) << std::endl;
}

BitString MonkeyDuplex::step(BitString I, size_t extract_bits){
    assert(I.size() <= r-2);
    assert(extract_bits <= r);

    I = I || BitString::pad101(r, I.size());
    std::cout << I << std::endl;

    const uint8_t *s = const_cast<const BitString&>(I).array();
    std::cout << "aaa" << endl;
    for(int i=0; i<r/8; i++){
        std::cout << i << endl;
        state[i] ^= s[i];
    }
    std::cout << format_hex(state, STATE_BYTES) << std::endl;

    KeccakPStar(200,nstep)(state);
    return BitString(state, extract_bits);
}

