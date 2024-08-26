#ifndef WOTS_H
#define WOTS_H
#define SPX_WOTS_LEN1 67  // مقدار پیشنهادی؛ این مقدار ممکن است بسته به نیاز شما متفاوت باشد

#include "params.h"

void wots_pkgen(unsigned char pk[WOTS_L*HASH_BYTES], const unsigned char sk[SEED_BYTES], const unsigned char masks[(WOTS_W-1)*HASH_BYTES]);

void wots_sign(unsigned char sig[WOTS_L*HASH_BYTES], const unsigned char msg[HASH_BYTES], const unsigned char sk[SEED_BYTES], const unsigned char masks[(WOTS_W-1)*HASH_BYTES]);

void wots_verify(unsigned char pk[WOTS_L*HASH_BYTES], const unsigned char sig[WOTS_L*HASH_BYTES], const unsigned char msg[HASH_BYTES], const unsigned char masks[(WOTS_W-1)*HASH_BYTES]);

extern void expand_seed(unsigned char outseeds[WOTS_L*HASH_BYTES], const unsigned char inseed[SEED_BYTES]);
extern void gen_fullchains(unsigned char x[WOTS_L*HASH_BYTES], const unsigned char masks[(WOTS_W-1)*HASH_BYTES]);
 extern void chain_lengths(unsigned int *lengths, const unsigned char *msg);

#endif
