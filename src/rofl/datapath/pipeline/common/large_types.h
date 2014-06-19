/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __LARGE_TYPES_H__
#define __LARGE_TYPES_H__

#include <stdint.h>

/*
 * This header file defines a structure for a type of 128 bits
 * It is meant to be shared between Rofl-core, pipeline and xDPd
 */

// This is defined as a 16 vector so the pipeline doesn't has to deal with byte order at all (e.g. upper and lower u64, etc)
typedef struct uint128_{
	uint8_t val[16];
}uint128__t;

//This is a wrapper that helps accessing uin128__t types 
typedef struct wrap_u128{
	uint64_t hi;
	uint64_t lo;
} __attribute__ ((__may_alias__)) w128_t;

#define UINT128__T_HI(x) ((w128_t*)&x)->hi
#define UINT128__T_LO(x) ((w128_t*)&x)->lo

#define SWAP_U128(x) do{ \
	((w128_t*)&x)->hi = __bswap_64 (((w128_t*)&x)->hi); \
	((w128_t*)&x)->lo = __bswap_64 (((w128_t*)&x)->lo); \
}while(0)

#endif //__LARGE_TYPES_H__
