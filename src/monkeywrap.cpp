#include "monkeywrap.hpp"


namespace Krys {
    MonkeyWrap::MonkeyWrap(uint rho, uint nstart, uint nstep, uint nstride)
        : rho(rho), duplex(rho + 4, nstart, nstep, nstride) {}

    void MonkeyWrap::initialize(const BitString& K, const BitString& N) {
        // TODO: add asserts
        duplex.start(BitString::keypack(K, K.size() + 16) || N);
    }

    std::pair<Ciphertext, Tag> MonkeyWrap::wrap(
        const BitString& A, const BitString& B, uint ell
    ) {
        Ciphertext C;
        Blocks     Ab(A, rho), Bb(B, rho), Cb(C, rho); // TODO: implement own Blocks

        for (uint i = 0; i <= Ab.size() - 2; ++i) {
            duplex.step(Ab[i] || 0 || 0, 0);
        }
        BitString Z = duplex.step(Ab[Ab.size() - 1] || 0 || 1, Bb[0].size());
        Cb[0] = Bb[0] ^ Z;
        for ( unsigned int i = 0; i <= Bb.size() - 2; ++i ) {
            Z = duplex.step(Bb[i] || 1 || 1, Bb[i + 1].size());
            Cb[i + 1] = Bb[i + 1] ^ Z;
        }
        BitString T = duplex.stride(Bb[Bb.size() - 1] || 1 || 0, rho);
        while ( T.size() < ell ) {
            T = T || duplex.step(BitString(0), rho);
        }
        T.truncate(ell);

        return {C, T};
    }

    Plaintext MonkeyWrap::unwrap(
        const BitString& A, const BitString& C, const BitString& T
    ) {
        Plaintext plaintext;
        Blocks Ab(A, rho), Bb(plaintext, rho), Cb(C, rho);

        for (uint i = 0; i <= Ab.size() - 2; ++i) {
            duplex.step(Ab[i] || 0 || 0, 0);
        }
        BitString Z = duplex.step(Ab[Ab.size() - 1] || 0 || 1, Cb[0].size());
        Bb[0] = Cb[0] ^ Z;
        for (uint i = 0; i <= Cb.size() - 2; ++i) {
            Z = duplex.step(Bb[i] || 1 || 1, Cb[i + 1].size());
            Bb[i + 1] = Cb[i + 1] ^ Z;
        }
        BitString Tprime = duplex.stride(Bb[Cb.size() - 1] || 1 || 0, rho);
        while (Tprime.size() < T.size()) {
            Tprime = Tprime || duplex.step(BitString(0), rho);
        }
        Tprime.truncate(T.size());

        if (T != Tprime) {
            throw std::runtime_error("MonkeyWrapUnwrapError: Tags do not match after unwrap.");
        }
        return plaintext;
    }

}
