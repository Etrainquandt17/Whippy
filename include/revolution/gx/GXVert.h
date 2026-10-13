#ifndef REVOLUTION_GX_GXVERT_H
#define REVOLUTION_GX_GXVERT_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef union uPPCWGPipe {
    u8 u8;
    u16 u16;
    u32 u32;
    u64 u64;
    s8 s8;
    s16 s16;
    s32 s32;
    s64 s64;
    f32 f32;
    f64 f64;
} PPCWGPipe;

volatile PPCWGPipe GXWGFifo : 0xCC008000;

// TODO: these are static in the SDK. The original link folded every unit's copy into the first one; a static copy
// stays in a unit compiled from source and moves what follows it, so they are left to the linker as weak functions.
// TODO: with const parameters a caller reads a variable it passes at once; with plain ones it keeps the address and
// reads it at the call. scn/step/sfx/SpiralScreen.cpp has the second, gfx/TPLTexturePlate.cpp matches with the
// first, so a unit that needs the plain parameters defines REVOLUTION_GX_GXVERT_PLAIN_PARAMETERS ahead of its includes.
#ifdef REVOLUTION_GX_GXVERT_PLAIN_PARAMETERS
#define GXVERT_PARAMETER(T) T
#else
#define GXVERT_PARAMETER(T) const T
#endif

inline void GXPosition2f32(GXVERT_PARAMETER(f32) x, GXVERT_PARAMETER(f32) y) {
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
}

inline void GXPosition3f32(GXVERT_PARAMETER(f32) x, GXVERT_PARAMETER(f32) y, GXVERT_PARAMETER(f32) z) {
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.f32 = z;
}

inline void GXTexCoord2f32(GXVERT_PARAMETER(f32) s, GXVERT_PARAMETER(f32) t) {
    GXWGFifo.f32 = s;
    GXWGFifo.f32 = t;
}

inline void GXColor1u32(GXVERT_PARAMETER(u32) color) {
    GXWGFifo.u32 = color;
}

inline void GXEnd(void) {}

#ifdef __cplusplus
}
#endif

#endif
