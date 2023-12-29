#include <assert.h>
#include <iostream>

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

void MonkeyDuplex::start(std::string I){
  //TODO: input as BitString
  assert(I.length() <= STATE_BYTES-2);

  pad101(I, STATE_BYTES);
  I.copy((char*) state, STATE_BYTES);

  KeccakPStar(200,10)(state);
}
