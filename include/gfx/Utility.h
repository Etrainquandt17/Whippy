#ifndef GFX_UTILITY_H
#define GFX_UTILITY_H

#include "types.h"

namespace gfx {

class Utility {
public:
    static u32 CurrentGameWidth();
    static u32 CurrentGameHeight();
    static void SetupGXForScreen2D(f32, f32);
    static void SetupGXForLayout2D(f32, f32);
    static void SetupGXForLayout2D(f32, f32, f32, f32);
    static void SetZBufferRange(f32 nearZ, f32 farZ);
    static void SetGXStateDirty();
};

}

#endif
