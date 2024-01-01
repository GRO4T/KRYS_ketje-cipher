#include "monkeywrap.hpp"


namespace Krys {
    MonkeyWrap::MonkeyWrap(uint rho, uint nstart, uint nstep, uint nstride)
        : rho(rho), duplex(rho + 4, nstart, nstep, nstride) {}

    void MonkeyWrap::initialize(const BitString& key, const BitString& nonce) {
        // TODO: add asserts
        duplex.start(BitString::keypack(key, key.size() + 16) || nonce);
    }

    std::pair<Ciphertext, Tag> MonkeyWrap::wrap(
        const BitString& associated_data, const BitString& plaintext, uint extract_bits
    ) {
        Ciphertext ciphertext;
        Blocks     A(associated_data, rho), B(plaintext, rho), C(ciphertext, rho); // TODO: implement own Blocks

        for (uint i = 0; i <= A.size() - 2; ++i) {
            duplex.step(A[i] || 0 || 0, 0);
        }
        BitString Z = duplex.step(A[A.size() - 1] || 0 || 1, B[0].size());
        C[0] = B[0] ^ Z;
        for ( unsigned int i = 0; i <= B.size() - 2; ++i ) {
            Z = duplex.step(B[i] || 1 || 1, B[i + 1].size());
            C[i + 1] = B[i + 1] ^ Z;
        }
        BitString tag = duplex.stride(B[B.size() - 1] || 1 || 0, rho);
        while ( tag.size() < extract_bits ) {
            tag = tag || duplex.step(BitString(0), rho);
        }
        tag.truncate(extract_bits);

        return {ciphertext, tag};
    }

    Plaintext MonkeyWrap::unwrap(
        const BitString& associated_data, const BitString& ciphertext, const BitString& tag
    ) {
        Plaintext plaintext;
        Blocks A(associated_data, rho), B(plaintext, rho), C(ciphertext, rho);

        for (uint i = 0; i <= A.size() - 2; ++i) {
            duplex.step(A[i] || 0 || 0, 0);
        }
        BitString Z = duplex.step(A[A.size() - 1] || 0 || 1, C[0].size());
        B[0] = C[0] ^ Z;
        for (uint i = 0; i <= C.size() - 2; ++i) {
            Z = duplex.step(B[i] || 1 || 1, C[i + 1].size());
            B[i + 1] = C[i + 1] ^ Z;
        }
        BitString unwraped_tag = duplex.stride(B[C.size() - 1] || 1 || 0, rho);
        while (unwraped_tag.size() < tag.size()) {
            unwraped_tag = unwraped_tag || duplex.step(BitString(0), rho);
        }
        unwraped_tag.truncate(tag.size());

        if (tag != unwraped_tag) {
            throw std::runtime_error("MonkeyWrapUnwrapError: Tags do not match after unwrap.");
        }
        return plaintext;
    }

}
