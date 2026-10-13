#ifndef SCN_STEP_SFX_BGFADE_H
#define SCN_STEP_SFX_BGFADE_H

#include "revolution/gx/GXStruct.h"
#include "sfx/Fade.h"
#include "types.h"

namespace scn {
namespace step {
namespace sfx {

class BGFade {
public:
    BGFade();

    void update();
    void setFadeIn(u32 frame);
    void setFadeOut(u32 frame);
    void setColor(const GXColor& color);
    bool isNeedToDraw() const;
    void draw() const;

private:
    ::sfx::Fade mFade;
};

}
}
}

#endif
