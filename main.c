#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "crypto_aead.h"


int do_test_crypto_aead(
    const unsigned char *key,           unsigned long long keyLen,
    const unsigned char *nonce,         unsigned long long nonceLen,
    const unsigned char *AD,            unsigned long long ADlen,
    const unsigned char *plaintext,     unsigned long long plaintextLen,
    const unsigned char *ciphertext,
    unsigned int tagLen,
    unsigned char *temp1,
    unsigned char *temp2
    )
{
    unsigned long long clen, mlen, i;

    if (crypto_aead_encrypt(temp1, &clen, plaintext, plaintextLen, AD, ADlen, 0, nonce, key) != 0) {
        printf("!!! crypto_aead_encrypt() did not return 0.\n");
        return 1;
    }
    if (clen != plaintextLen+tagLen) {
        printf("!!! clen does not have the expected value.\n");
        return 1;
    }
    if (memcmp(temp1, ciphertext, (size_t)clen) != 0) {
        printf("!!! The output of crypto_aead_encrypt() is not as expected.\n");
        return 1;
    }

    if (crypto_aead_decrypt(temp1, &mlen, 0, ciphertext, plaintextLen+tagLen, AD, ADlen, nonce, key) != 0) {
        printf("!!! crypto_aead_decrypt() did not return 0.\n");
        return 1;
    }
    if (mlen != plaintextLen) {
        printf("!!! mlen does not have the expected value.\n");
        return 1;
    }
    if (memcmp(temp1, plaintext, (size_t)mlen) != 0) {
        printf("!!! The output of crypto_aead_decrypt() is not as expected.\n");
        return 1;
    }

    memcpy(temp2, ciphertext, (size_t)(plaintextLen+tagLen));
    temp2[0] ^= 0x01;
    if (crypto_aead_decrypt(temp1, &mlen, 0, temp2, plaintextLen+tagLen, AD, ADlen, nonce, key) == 0) {
        printf("!!! Forgery found :-)\n");
        return 1;
    }
    for(i=0; i<plaintextLen; i++) if (temp1[i] != 0) {
        printf("!!! The output buffer is not cleared.\n");
        return 1;
    }

    printf("Self-test OK\n");
    return 0;
}

int test_crypto_aead(
    const unsigned char *key,           unsigned long long keyLen,
    const unsigned char *nonce,         unsigned long long nonceLen,
    const unsigned char *AD,            unsigned long long ADlen,
    const unsigned char *plaintext,     unsigned long long plaintextLen,
    const unsigned char *ciphertext,
    unsigned int tagLen)
{
    unsigned char *temp1 = malloc((size_t)plaintextLen + tagLen);
    unsigned char *temp2 = malloc((size_t)plaintextLen + tagLen);
    int retcode = do_test_crypto_aead(key, keyLen, nonce, nonceLen, AD, ADlen, plaintext, plaintextLen, ciphertext, tagLen, temp1, temp2);
    free(temp1);
    free(temp2);
    return retcode;
}


int main(void) {
    const unsigned char *key = (const unsigned char *)
        "\x5a\x4b\x3c\x2d\x1e\x0f\x00\xf1\xe2\xd3\xc4\xb5\xa6\x97\x88\x79";
    const unsigned char *nonce_ = (const unsigned char *)
        "\x6b\x4c\x2d\x0e\xef\xd0\xb1\x92\x72\x53\x34\x15\xf6\xd7\xb8\x99";
    const unsigned char *AD = (const unsigned char *)
        "\x32\xf3\xb4\x75\x35\xf6";
    const unsigned char *plaintext = (const unsigned char *)
        "\xe4\x65\xe5\x66\xe6\x67\xe7";
    const unsigned char *ciphertext = (const unsigned char *)
        "\x0c\x20\x01\x37\x08\xb7\xdb\x7c\xe0\x47\xac\xd4\x69\xb7\x5c\xc1\xf2\xc3\x06\x76\x5b\xb5\x98";
    unsigned char nonce[181];
    memset(nonce, 0, 181);
    memcpy(nonce, nonce_, 16);
    return test_crypto_aead(key, 16, nonce, 181, AD, 6, plaintext, 7, ciphertext, 16);
}   