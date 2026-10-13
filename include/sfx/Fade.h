#ifndef SFX_FADE_H
#define SFX_FADE_H

#include "revolution/gx/GXStruct.h"
#include "types.h"

namespace sfx {

class Fade {
public:
    void update();
    void setColor(const GXColor& color);
    void setFadeOut(u32 frame);
    void setFadeIn(u32 frame);
    void draw() const;

private:
    u8 _0[0x140];
};

}

#endif
