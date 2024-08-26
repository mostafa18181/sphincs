#ifndef SPX_THASHX2_AS_ONE
#define SPX_THASHX2_AS_ONE

#include <stdint.h>
#include "context.h"
#include "thash.h"

#define SPX_ADDR_BYTES 32

void thash(unsigned char *out, const unsigned char *in, unsigned int inblocks,
           const spx_ctx *ctx, uint32_t addr[8]);


#endif

