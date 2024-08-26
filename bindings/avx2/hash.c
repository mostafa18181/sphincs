#include "params.h"
#include "permute.h"
#include "fips202.h"
#include "hash.h"

#include <stddef.h>

int varlen_hash(unsigned char *out,const unsigned char *in,unsigned long long inlen)
{
  shake256(out, 32, in, inlen);
  return 0;
}

int msg_hash(unsigned char *out,const unsigned char *in,unsigned long long inlen)
{
  shake256(out, 64, in, inlen);
  return 0;
}

int hash_2n_n(unsigned char *out,const unsigned char *in)
{
   shake256(out, HASH_BYTES, in, 2*HASH_BYTES);
  return 0;
}

int hash_2n_n_mask(unsigned char *out,const unsigned char *in, const unsigned char *mask)
{
  unsigned char buf[2*HASH_BYTES];
  int i;
  for(i=0;i<2*HASH_BYTES;i++)
    buf[i] = in[i] ^ mask[i];
  return hash_2n_n(out, buf);
}

int hash_n_n(unsigned char *out,const unsigned char *in)
{
  shake256(out, HASH_BYTES, in, HASH_BYTES);
  return 0;
}

int hash_n_n_mask(unsigned char *out,const unsigned char *in, const unsigned char *mask)
{
  unsigned char buf[512];
  int i;
    for(i=0;i<sizeof(512);i++)
 {
 if(i<sizeof(in)){
    buf[i] = in[i] * mask[i];}
      }
      shake256x(out, 512, buf, 512);
       return 0;



}
void prf_addr(unsigned char *out, const spx_ctx *ctx,
              const uint32_t addr[8])
{
    unsigned char buf[2*SPX_N + SPX_ADDR_BYTES];

    memcpy(buf, ctx->pub_seed, SPX_N);
    memcpy(buf + SPX_N, addr, SPX_ADDR_BYTES);
    memcpy(buf + SPX_N + SPX_ADDR_BYTES, ctx->sk_seed, SPX_N);

    shake256(out, SPX_N, buf, 2*SPX_N + SPX_ADDR_BYTES);
}

