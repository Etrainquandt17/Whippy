#ifndef GFX_FULLSCREENPLATE_H
#define GFX_FULLSCREENPLATE_H

#include "revolution/gx/GXStruct.h"
#include "types.h"

namespace gfx {

class FullScreenPlate {
public:
    FullScreenPlate(const GXColor& color);

    void draw() const;
    void setColor(const GXColor& color);
    void setAlpha(f32 alpha);

private:
    GXColor mColor;
    f32 mAlpha;
};

}  // namespace gfx

#endif
