/*
 * Copyright (C) 2013-2014 Synopsys, Inc. All rights reserved.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __ASM_ARC_TYPES_H
#define __ASM_ARC_TYPES_H

// typedef unsigned short umode_t;

// /*
 // * __xx is ok: it doesn't pollute the POSIX namespace. Use these in the
 // * header files exported to user space
 // */

// typedef __signed__ char __s8;
// typedef unsigned char __u8;

// typedef __signed__ short __s16;
// typedef unsigned short __u16;

// typedef __signed__ int __s32;
// typedef unsigned int __u32;

// #if defined(__GNUC__) && !defined(__STRICT_ANSI__)
// typedef __signed__ long long __s64;
// typedef unsigned long long __u64;
// #endif

// /*
 // * These aren't exported outside the kernel to avoid name space clashes
 // */
// typedef signed char s8;
// typedef unsigned char u8;

// typedef signed short s16;
// typedef unsigned short u16;

// typedef signed int s32;
// typedef unsigned int u32;

// typedef signed long long s64;
// typedef unsigned long long u64;

// #define BITS_PER_LONG 32

// /* Dma addresses are 32-bits wide. */

// typedef u32 dma_addr_t;

typedef unsigned long phys_addr_t;
typedef unsigned long phys_size_t;

#endif /* __ASM_ARC_TYPES_H */
