#ifndef SCN_STEP_ENEMY_BABUT_PARAMDATA_H
#define SCN_STEP_ENEMY_BABUT_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace babut {

// TODO: the name is a guess: nothing in the game names what Param::babut() returns. The members named after
// their offsets and whatever follows the last one are not known yet.
struct ParamData {
    u32 _0[2];
    f32 mSinCurveHeight;
    f32 mSinCurveFreq;
    f32 mSinCurveSpeedX;
    u32 mAttackDamageWait;
    u32 mAttackDamage;
    u32 mAttackFrame;
    f32 mEscapeAccelV;
    f32 mEscapeSpeedVMax;
    s32 mStandBackFrame;
    f32 mStandBackHeight;
    u32 mStandBackWait;
    f32 mTakeOffHeight;
    s32 mTakeOffFrame;
    u32 _3c;
    u32 mTakeOffSoundFrame;
    gobj::MoveParamAccel mStandBackAccel;
    u32 mSinCurveDescendFrame;
    f32 mSinCurveDescendHeight;
    f32 mDifficultyRateLv0;
    f32 mDifficultyRateLv1;
    f32 mDifficultyRateLv2;
    u32 _64[8];
    f32 mSearchRadius;
    f32 mSearchOffsetY;
};

}
}
}
}

#endif
