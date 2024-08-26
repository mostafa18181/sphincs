#define SUBTREE_HEIGHT 5
#define TOTALTREE_HEIGHT 60
#define N_LEVELS (TOTALTREE_HEIGHT/SUBTREE_HEIGHT)
#define SEED_BYTES 32
#define WOTS_LOGW 4

#define SK_RAND_SEED_BYTES 32
#define MESSAGE_HASH_SEED_BYTES 32
#define SPX_FORS_BYTES 32
#define SPX_WOTS_BYTES 2144
#define SPX_TREE_HEIGHT 7
#define SPX_FORS_MSG_BYTES 32
#define SPX_WOTS_LEN 67
#define SPX_N 32
#define SPX_D 6

#define HORST_LOGT 16
#define HORST_T (1<<HORST_LOGT)
#define HORST_K 32
#define HORST_SKBYTES 32
#define HORST_SIGBYTES (64*HASH_BYTES+(((HORST_LOGT-6)*HASH_BYTES)+HORST_SKBYTES)*HORST_K)

#define WOTS_W (1 << WOTS_LOGW)
#define WOTS_L1 ((256+WOTS_LOGW-1)/WOTS_LOGW)
#define WOTS_L 67  // for WOTS_W == 16
#define WOTS_LOG_L 7  // for WOTS_W == 16
#define WOTS_SIGBYTES (WOTS_L*HASH_BYTES)

#define HASH_BYTES 32 // Has to be log(HORST_T)*HORST_K/8
#define MSGHASH_BYTES 64

#define N_MASKS (2*(HORST_LOGT)) /* has to be the max of  (2*(SUBTREE_HEIGHT+WOTS_LOGL)) and (WOTS_W-1) and 2*HORST_LOGT */
#define SPX_NAMESPACE(name) name
#define SPX_OFFSET_LAYER 0
#define SPX_OFFSET_TREE 1
#define SPX_OFFSET_TYPE 2
#define SPX_OFFSET_KP_ADDR 3
#define SPX_OFFSET_CHAIN_ADDR 4
#define SPX_OFFSET_HASH_ADDR 5
#define SPX_OFFSET_TREE_HGT 6
#define SPX_OFFSET_TREE_INDEX 7
#define CRYPTO_SEEDBYTES 32
#define SPX_FULL_HEIGHT 60

#define SPX_BYTES (SPX_N * (1 + SPX_FULL_HEIGHT + ((SPX_D - 1) * (SPX_WOTS_BYTES + SPX_TREE_HEIGHT * SPX_N))))
#ifndef PARAMS_H
#define PARAMS_H


#define SPX_N 32
#define SPX_FULL_HEIGHT 60
#define SPX_D 12
#define SPX_FORS_TREES 15
#define SPX_FORS_HEIGHT 5



#endif

#include "context.h"
