#include <assert.h>
#include <iostream>

#include "monkeyduplex.hpp"
#include "utils.hpp"

extern "C"{
  #include "KeccakP-200-SnP.h"
}

MonkeyDuplex::MonkeyDuplex(unsigned int r, unsigned int nstart, unsigned int nstep, unsigned int nstride)
      : r(r),
        nstart(nstart),
        nstep(nstep),
        nstride(nstride){
    assert(nstep < nstride);
    assert(r < STATE_BYTES);
};

void MonkeyDuplex::start(std::string I){
  assert(I.length() <= STATE_BYTES-2);

  std::cout << "monkeyduplex init I:          " << string_to_hex(I) << " length " << I.length() << std::endl;
  pad101(I, STATE_BYTES);
  I.copy(state, STATE_BYTES);
  std::cout << "monkeyduplex init I (padded): " << string_to_hex(I) << " length " << I.length() << std::endl;
  std::cout << "monkeyduplex init I (padded) length: " << I.length() << std::endl;
  KeccakP200_Permute_Nrounds(state, 10);
  std::cout << "monkeyduplex init I (after perm): " << string_to_hex(state) << std::endl;
}
