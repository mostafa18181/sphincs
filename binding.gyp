{
 "variables": {
    "openssl_fips": ""
  },
  "targets": [
    {
      "target_name": "sphincsplus",
      "sources": [
               "bindings/sphincsplus.cpp",
               "bindings/avx2/sign.c",
               "bindings/avx2/wots.c",
               "bindings/avx2/fips202.c",
               "bindings/avx2/prg.c",
               "bindings/avx2/randombytes.c",
               "bindings/avx2/hash.c",
               "bindings/avx2/hash_4x.c",
               "bindings/avx2/fips202x4.c",
                         "bindings/avx2/thash.c",
                              "bindings/avx2/context.h",
                                             "bindings/avx2/merkle.c",
                                             "bindings/avx2/address.c",
                                                     "bindings/avx2/wotsx1.c",

                "bindings/avx2/utilsx1.c",
                           "bindings/avx2/utils.c",
               "bindings/avx2/XKCP-master/lib/low/KeccakP-1600/plain-64bits/KeccakP-1600-unrolling.macros",
               "bindings/avx2/XKCP-master/lib/low/KeccakP-1600/plain-64bits/KeccakP-1600-opt64.c",
               "bindings/avx2/XKCP-master/lib/low/KeccakP-1600/plain-64bits/KeccakP-1600-unrolling.macros",
               "bindings/avx2/XKCP-master/lib/low/KeccakP-1600/plain-64bits/SnP-Relaned.h"

      ],
      "include_dirs": [
        "<!(node -p \"require('node-addon-api').include\")",
      "<!(pkg-config --cflags-only-I openssl)",

        "bindings/avx2",
        "include"
      ],
      "cflags": [
        "-std=c11",
        "-Wall",
        "-mavx2",
        "-mbmi2",
        "-O3",
        "-Wextra",
        "-std=c11"
      ],
      "cflags_cxx": [
        "-std=c++11",
        "-Wall",
        "-Wextra"
      ],
            "libraries": [
              "<!(pkg-config --libs openssl)"
            ]
    },
    {
      "target_name": "myaddon",
      "sources": [
        "bindings/avx2/myaddon.cpp",
        "bindings/avx2/sign.c",
        "bindings/avx2/randombytes.c",
        "bindings/avx2/fips202.c",
        "bindings/avx2/wots.c",
        "bindings/avx2/prg.c",
         "bindings/avx2/hash.c",
        "bindings/avx2/hash_4x.c",
        "bindings/avx2/fips202x4.c",
                   "bindings/avx2/thash.c",
                                      "bindings/avx2/context.h",
                                         "bindings/avx2/merkle.c",
                       "bindings/avx2/address.c",
                           "bindings/avx2/wotsx1.c",
                            "bindings/avx2/utilsx1.c",
                                          "bindings/avx2/utils.c",
        "bindings/avx2/XKCP-master/lib/low/KeccakP-1600/plain-64bits/KeccakP-1600-opt64.c",
        "bindings/avx2/XKCP-master/lib/low/KeccakP-1600/plain-64bits/KeccakP-1600-unrolling.macros",
        "bindings/avx2/XKCP-master/lib/low/KeccakP-1600/plain-64bits/KeccakP-1600-unrolling.macros",
        "bindings/avx2/XKCP-master/lib/low/KeccakP-1600/plain-64bits/SnP-Relaned.h"


      ],
      "include_dirs": [
        "<!(node -p \"require('node-addon-api').include\")"
      ],
      "cflags": [
        "-std=c++11",
        "-Wall",
        "-mavx2",
        "-Wextra"
      ],
      "cflags_cxx": [
        "-std=c++11",
        "-Wall",
        "-Wextra"
      ]
    }
  ]
}
