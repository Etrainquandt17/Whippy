#ifndef SCN_STEP_BOSS_ATTACKFLASH_H
#define SCN_STEP_BOSS_ATTACKFLASH_H

#include "revolution/gx/GXStruct.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class AttackFlash {
public:
    AttackFlash();

    void update();
    void setStart(GXColor color);
    void setContinue();
    void setEnd(GXColor color);
    void cancel();
    void setAlphaIncRate(f32 rate);
    bool isValid() const;
    GXColor getColor() const;

private:
    GXColor mColor;
    u32 mState;
    f32 mAngle;
    f32 mAlpha;
    f32 mAlphaIncRate;
};

}}}  // namespace scn::step::boss

#endif
