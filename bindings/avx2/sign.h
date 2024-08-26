#ifndef SIGN_H
#define SIGN_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stddef.h>
#include <stdint.h>

#define CRYPTO_SECRETKEYBYTES 64
#define CRYPTO_PUBLICKEYBYTES 32
#define CRYPTO_BYTES 64
#define CRYPTO_SEEDBYTES 512

// typedef struct {
//     unsigned char sk_seed[32];
//     unsigned char pub_seed[32];
// } spx_ctx;

typedef struct {
    unsigned char sk_seed[32];
    unsigned char pub_seed[32];
    unsigned char state[25];
} spx_cty;
 int crypto_sign_keypair(unsigned char *pk, unsigned char *sk);
int crypto_sign(unsigned char *sm, unsigned long long *smlen,
                const unsigned char *m, unsigned long long mlen,
                const unsigned char *sk);
int crypto_sign_verify(const unsigned char *sig, size_t siglen,
                       const unsigned char *m, size_t mlen, const unsigned char *pk);
#ifdef __cplusplus
}
#endif
#endif // SIGN_H

