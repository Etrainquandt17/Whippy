#ifndef SCN_STEP_ENEMY_SCARFY_PARAMDATA_H
#define SCN_STEP_ENEMY_SCARFY_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace scarfy {

// TODO: the name is a guess: nothing in the game names what Param::scarfy() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    struct Level {
        f32 mSpd;
        f32 mSpdLimit;
    };

    f32 mFlyUpDownAngleSpeed;
    f32 mFlyUpDownHeight;
    f32 mChaseTargetOffsetY;
    u32 _c[0x34 / 4];
    Level mLevel[5];
    f32 mFaceChangeSpeedV;
    u32 _6c;
    u32 mFaceChangeAccelFrame;
    u32 mFaceChangeEndFrame;
    u32 _78;
    gobj::MoveParamAccel mFaceChangeAccel;
    u32 _88[3];
    gobj::MoveParamFall mFaceChangeFall;
    f32 mFaceChangeFlipFrame;
    u32 mWhispyAppearFrame1;
    u32 mWhispyAppearFrame2;
    f32 mWhispyAppearRotSpeed;
    f32 mWhispyAppearHeight1;
    f32 mWhispyAppearHeight2;
    f32 mEscapeAccelX;
    f32 mEscapeSpeedLimitX;
    f32 mEscapeAccelY;
    f32 mEscapeSpeedLimitY;
};

}
}
}
}

#endif
