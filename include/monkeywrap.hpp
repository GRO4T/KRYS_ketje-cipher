#pragma once

#include <utility>

#include "bitstring.h"
#include "monkeyduplex.hpp"


namespace Krys {
    using Ciphertext = BitString;
    using Tag = BitString;

    class MonkeyWrap {
      public:
        MonkeyWrap(uint rho, uint nstart, uint nstep, uint nstride);
        void initialize(const BitString& K, const BitString& N);
        std::pair<Ciphertext, Tag> wrap(
            const BitString& A, const BitString& B, uint ell
        );
      private:
        uint rho;
        MonkeyDuplex duplex;
    };
}
