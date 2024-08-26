#ifndef HASH_4X_H
#define HASH_4X_H

#include "params.h"

int loop_hash_2n_n_mask_4x(unsigned char *out, const unsigned char *in,
                           unsigned long long blocks_4x, const unsigned char *mask);

int hash_2n_n_mask_4x(unsigned char *out, const unsigned char *in,
                      unsigned long long out_dist, unsigned long long in_dist,
                      const unsigned char *mask);

int hash_n_n_4x(unsigned char *out, const unsigned char *in);

int hash_n_n_mask_4x(unsigned char *out, const unsigned char *in, const unsigned char *mask);

#endif // HASH_4X_H
