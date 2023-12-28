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
        "\x14\x5e\xa8\xf2\x3d\x87\xd1\x1c\x66\xb0\xfa\x45";
    const unsigned char *nonce = (const unsigned char *)
        "\x15\x70\xcb\x27\x82\xdd\x39\x94\xef\x4b";
    const unsigned char *AD = (const unsigned char *)
        "\x0c\x78\xe4\x51\xbd\x2a";
    const unsigned char *plaintext = (const unsigned char *)
        "\x0e\x8b\x09\x86\x04\x81\xfe";
    const unsigned char *ciphertext = (const unsigned char *)
        "\x9d\x09\x58\x2b\xce\xff\xd6\x44\x7b\x5e\xeb\x2b\xa5\x5a\x85\x11\xbc\xd0\x06";
    return test_crypto_aead(key, 12, nonce, 10, AD, 6, plaintext, 7, ciphertext, 12);
}
