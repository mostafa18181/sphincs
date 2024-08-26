
#include <stddef.h>
#include <string.h>
#include "crypto_sign.h"
#include "hash.h"
#include "wots.h"
#include "merkle.h"
#include "randombytes.h"
#include "params.h"
#include "address.h"
#include "utils.h"
#include "fips202.h"
#include "sign.h"
#include "thash.h"
#include "context.h"
#include "wotsx1.h"
#include "utilsx1.h"


void PrintHex(  const unsigned char* data, size_t length) {

    for (size_t i = 0; i < length; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int crypto_sign_keypair(unsigned char *pk, unsigned char *sk) {
    spx_ctx ctx;
    unsigned char seed[SPX_N];

    // تولید یک seed تصادفی برای کلید خصوصی
    randombytes(seed, SPX_N);






    // ذخیره seed به عنوان sk_seed در کلید خصوصی
    memcpy(sk, seed, SPX_N);
    memcpy(ctx.sk_seed, seed, sizeof(ctx.sk_seed));

    // تولید pub_seed و ذخیره آن در کلید عمومی
    prf_addr(pk, &ctx, (const uint32_t[8]){0});

    // ذخیره pub_seed در کلید خصوصی نیز
    memcpy(sk + SPX_N, pk, SPX_N);
    memcpy(ctx.pub_seed, pk, sizeof(ctx.pub_seed));

    // تولید ریشه مرکل (Merkle root) برای کلید عمومی
    merkle_gen_root(pk + SPX_N, &ctx);
}
int crypto_sign(unsigned char *signature, unsigned long long *smlen, const unsigned char *message, unsigned long long mlen, const unsigned char *sk) {

    spx_ctx ctx;
    unsigned char mhash[SPX_N];
//     unsigned char root[SPX_N];

//     unsigned char wots_sig[SPX_WOTS_BYTES];
    unsigned char *wots_sig = (unsigned char*)malloc(SPX_WOTS_BYTES*5);
unsigned char *root = (unsigned char*)malloc(SPX_N*5);

    uint32_t wots_addr[8] = {0};
    uint32_t tree_addr[8] = {0};

    // مقداردهی اولیه context
    memcpy(ctx.sk_seed, sk, SPX_N);
    memcpy(ctx.pub_seed, sk + SPX_N, SPX_N);

    // محاسبه هش پیام
    shake256(mhash, SPX_N, message, mlen);

    // تولید WOTS signature
    wots_sign(wots_sig, mhash, ctx.sk_seed, sk + 2*SPX_N);

    // ترکیب WOTS signature و مسیر احراز هویت مرکل
    merkle_sign(signature, root, &ctx, wots_addr, tree_addr, 0);

    // محاسبه طول امضا
    *smlen = SPX_WOTS_BYTES + SPX_TREE_HEIGHT * SPX_N;

   free(wots_sig);
   wots_sig = NULL;
   free(root);
   root = NULL;


}
int crypto_sign_verify(const unsigned char *signature, size_t siglen, const unsigned char *message, size_t mlen, const unsigned char *pk) {
    spx_ctx ctx;
    unsigned char mhash[SPX_N];
    unsigned char root[SPX_N];
    unsigned char wots_pk[SPX_WOTS_BYTES];
    uint32_t wots_addr[8] = {0};
    uint32_t tree_addr[8] = {0};

    // مقداردهی اولیه context
    memcpy(ctx.pub_seed, pk, SPX_N);

    // محاسبه هش پیام
    shake256(mhash, SPX_N, message, mlen);

    // بازسازی کلید عمومی WOTS از امضا
    wots_verify(wots_pk, signature, mhash, pk + SPX_N);

    // بازسازی ریشه درخت مرکل
    compute_root(root, wots_pk, 0, 0, signature + SPX_WOTS_BYTES, SPX_TREE_HEIGHT, &ctx, tree_addr);

    // مقایسه ریشه درخت مرکل بازسازی شده با کلید عمومی ارائه شده
    if (memcmp(root, pk + SPX_N, SPX_N) == 0) {
        return 0;  // امضا معتبر است
    } else {
        return -1;  // امضا نامعتبر است
    }
}
