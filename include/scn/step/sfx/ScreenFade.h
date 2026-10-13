#ifndef SCN_STEP_SFX_SCREENFADE_H
#define SCN_STEP_SFX_SCREENFADE_H

#include "revolution/gx/GXStruct.h"
#include "types.h"

namespace scn {
namespace step {
namespace sfx {

// TODO: members and the other functions.
class ScreenFade {
public:
    void setColor(const GXColor& color);
    void setFadeIn(u32 frame);
    void setFadeOut(u32 frame);
    void setStopFrame(u32 frame);
    bool isEnd() const;
};

}
}
}

#endif
