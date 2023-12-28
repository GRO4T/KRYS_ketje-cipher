#pragma once

#include <string>

// Ketje Jr: keccak-pstar[200]
#define STATE_BYTES 25

//TODO: make generic for all state sizes
class MonkeyDuplex{
  public:
    MonkeyDuplex(unsigned int r, unsigned int nstart, unsigned int nstep, unsigned int nstride);
    void start(std::string I);
  private:
    char state[STATE_BYTES];
    unsigned int r;
    unsigned int nstart;
    unsigned int nstep;
    unsigned int nstride;
};
