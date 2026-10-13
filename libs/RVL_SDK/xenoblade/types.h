#ifndef TYPES_H
#define TYPES_H

#ifdef __cplusplus
#include <xenoblade/PowerPC_EABI_Support/include/stl/cstdarg>
#include <xenoblade/PowerPC_EABI_Support/include/stl/cstddef>
#include <xenoblade/PowerPC_EABI_Support/include/stl/cstdint>
#include <xenoblade/PowerPC_EABI_Support/include/stl/new>
#else
#include <xenoblade/PowerPC_EABI_Support/include/stl/stdarg.h>
#include <xenoblade/PowerPC_EABI_Support/include/stl/stddef.h>
#include <xenoblade/PowerPC_EABI_Support/include/stl/stdint.h>
#endif

#include <xenoblade/compat.h>
#include <xenoblade/decomp.h>
#include <xenoblade/lang.h>
#include <xenoblade/macros.h>
#include <xenoblade/build_settings.h>

typedef unsigned long long u64;
typedef signed long long s64;

typedef unsigned long u32;
typedef signed long s32;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned char u8;
typedef signed char s8;

typedef float f32;
typedef double f64;

typedef unsigned int uint;

typedef int UNKWORD;
typedef void UNKTYPE;

enum { FALSE, TRUE };
typedef int BOOL;

#endif
