#include <stdint.h>
#include <string.h>

#include "context.h"
#include "params.h"
#include "utils.h"
#include "fips202.h"

void thash(unsigned char *out,
           const unsigned char *in,
           unsigned int inblocks,
           const spx_ctx *ctx, uint32_t addr[8])
{
    unsigned char buf[SPX_N + 32 + inblocks * SPX_N];
    unsigned char bitmask[inblocks * SPX_N];
    unsigned int i;

    memcpy(buf, ctx->pub_seed, SPX_N);
    memcpy(buf + SPX_N, addr, 32);

    // استفاده از shake256 برای ایجاد ماسک
    shake256(bitmask, inblocks * SPX_N, buf, SPX_N + 32);

    // XOR کردن ورودی با bitmask
    for (i = 0; i < inblocks * SPX_N; i++) {
        buf[SPX_N + 32 + i] = in[i] ^ bitmask[i];
    }

    // هش نهایی با استفاده از shake256
    shake256(out, SPX_N, buf, SPX_N + 32 + inblocks * SPX_N);
}
