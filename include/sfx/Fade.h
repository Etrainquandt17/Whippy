#ifndef SFX_FADE_H
#define SFX_FADE_H

#include "hel/math/Vector2.h"
#include "revolution/gx/GXStruct.h"
#include "types.h"

namespace sfx {

class Fade {
public:
    // TODO: the game names neither 0 (after a fade in, nothing is drawn) nor 1 (after a fade out, all is covered);
    // the others are named after the setters.
    enum State {
        STATE_0,
        STATE_1,
        STATE_FADE_IN,
        STATE_FADE_OUT,
        STATE_WIPE_IN,
        STATE_WIPE_OUT,
        STATE_WIPE_STAR_IN,
        STATE_WIPE_STAR_OUT,
    };

    Fade();

    void update();
    void setColor(const GXColor& color);
    void setFadeOut(u32 frame);
    void setFadeIn(u32 frame);
    void setWipeIn(u32 frame, const hel::math::Vector2& center);
    void setWipeOut(u32 frame, const hel::math::Vector2& center);
    void setWipeStarIn(u32 frame, const hel::math::Vector2& center);
    void setWipeStarOut(u32 frame, const hel::math::Vector2& center);
    void setStopFrame(u32 frame);
    bool isNeedToDraw() const;
    bool isEnd() const;
    f32 frame() const;
    f32 totalFrame() const;
    void draw() const;
    void draw(f32, f32) const;
    void drawIN(bool, f32, f32) const;

private:
    bool _0;
    f32 mAlpha;
    hel::math::Vector2 mCenter;
    State mState;
    GXColor mColor;
    u32 mFrame;
    u32 mFrameMax;
    u32 mStopFrame;
};

}  // namespace sfx

#endif
