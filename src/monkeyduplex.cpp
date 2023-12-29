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
  //TODO: input as BitString
  assert(I.size() <= STATE_BITS-2);
  std::cout << I << std::endl;

  I = I || BitString::pad101(STATE_BITS, I.size());
  std::cout << I << std::endl;
  memcpy(state, I.array(), STATE_BYTES);

  KeccakPStar(200,10)(state);
  std::cout << format_hex(state, STATE_BYTES) << std::endl;
}

