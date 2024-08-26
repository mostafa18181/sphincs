#ifndef SPX_FIPS202_H
#define SPX_FIPS202_H

#define SHAKE128_RATE 168
#define SHAKE256_RATE 136
#include <stdint.h>
#include <stddef.h>
/* Evaluates SHAKE-128 on `inlen' bytes in `in', according to FIPS-202.
 * Writes the first `outlen` bytes of output to `out`.
 */
void shake128(unsigned char *out, unsigned long long outlen,
              const unsigned char *in, unsigned long long inlen);

/* Evaluates SHAKE-256 on `inlen' bytes in `in', according to FIPS-202.
 * Writes the first `outlen` bytes of output to `out`.
 */
void shake256(unsigned char *out, unsigned long long outlen,
              const unsigned char *in, unsigned long long inlen);
void shake256x(uint8_t *output, size_t outlen,
              const uint8_t *input, size_t inlen);
 void keccak_absorb(uint64_t *s, unsigned int r,
                          const unsigned char *m, unsigned long long mlen,
                          unsigned char p);
#endif
