#ifndef NREL_EZRENDER_RENDER2D_H
#define NREL_EZRENDER_RENDER2D_H

#include "nw4r/ut/ut_Rect.h"
#include "revolution/gx/GXStruct.h"

namespace nrel {
namespace ezrender {

// TODO: the other functions.
class Render2D {
public:
    static void renderRect(const nw4r::ut::Rect& rect, const GXColor& color);
};

}}  // namespace nrel::ezrender

#endif
