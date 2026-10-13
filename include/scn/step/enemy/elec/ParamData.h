#ifndef SCN_STEP_ENEMY_ELEC_PARAMDATA_H
#define SCN_STEP_ENEMY_ELEC_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace elec {

// TODO: the name is a guess: nothing in the game names what Param::elec() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    struct Level {
        f32 mMoveSpeed;
        f32 mMoveSpeedCharge;
        f32 mMoveSpeedAttack;
        f32 mChaseSpeed;
    };

    f32 mOffsetY;
    Level mLevel[3];
    f32 mFrameRateMax;
    int mAttackFrame;
    int mChargeFrame;
    int mWaitFrame;
    f32 _44;
    u32 mChaseWaitFrame;
    f32 mChaseNearDist;
    u32 mChaseNearFrame;
    int mAttackEndFrame;
    f32 _58;
    int _5c;
    int _60;
};

}}}}  // namespace scn::step::enemy::elec

#endif
