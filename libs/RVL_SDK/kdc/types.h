#ifndef TYPES_H
#define TYPES_H

#ifdef __cplusplus
#include <kdc/cstdarg>
#include <kdc/cstddef>
#include <kdc/new>
#else
#include <kdc/stdarg.h>
#include <kdc/stddef.h>
#endif

#include <kdc/compat.h>
#include <kdc/decomp.h>
#include <kdc/lang.h>
#include <kdc/macros.h>

typedef unsigned char byte_t;
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

typedef int UNKWORD;
typedef void UNKTYPE;

enum { FALSE, TRUE };
typedef int BOOL;

typedef void (*funcptr_t)(void);

#define nullptr NULL
#define override

#endif
