#ifndef SCN_STEP_ENEMY_GIGATZO_PARAMDATA_H
#define SCN_STEP_ENEMY_GIGATZO_PARAMDATA_H

#include "revolution/gx/GXStruct.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace gigatzo {

// TODO: the name is a guess: nothing in the game names what Param::gigatzo() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 mAimFrame1;
    u32 mAimFrame2;
    u32 mAimFrame3;
    f32 mAimSwing;
    u32 mEffectFrameSuper;
    u32 mEffectFrameCannon;
    u32 mEffectFrame;
    u32 mShotFrame;
    f32 mShadowDiameter;
    f32 mAimArea;
    u32 mWaitAttackTime[6];
    u32 mWaitBackAttackTime[4];
    u32 mWaitBackAttackMoreTime[3];
    f32 mCullingMargin;
    f32 mCullingMarginBack;
    GXColor mColor[7];
    f32 mBackZ;
};

}
}
}
}

#endif
