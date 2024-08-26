
#include <openssl/rand.h>
#include <openssl/sha.h>
#include "randombytes.h"
void randombytes(unsigned char *output, int size) {

    unsigned char buffer1[size];
    unsigned char buffer2[size];
    unsigned char combined[SHA256_DIGEST_LENGTH];

    // First source
    RAND_bytes(buffer1, size);

    // Second source
    RAND_bytes(buffer2, size);

    // Combine with SHA-256
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, buffer1, size);
    SHA256_Update(&sha256, buffer2, size);
    SHA256_Final(combined, &sha256);

    // Output the strong random bytes
    memcpy(output, combined, SHA256_DIGEST_LENGTH);
}