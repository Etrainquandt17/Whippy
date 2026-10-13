#ifndef SCN_STEP_ENEMY_NEEDLOUS_PARAMDATA_H
#define SCN_STEP_ENEMY_NEEDLOUS_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace needlous {

// TODO: the name is a guess: nothing in the game names what Param::needlous() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    gobj::MoveParamDecel mDecel;
    gobj::MoveParamFall mFall;
    gobj::MoveParamAccel mAttackAccel;
    f32 mMoveDist;
    u32 mWalkFrame;
    u32 mAttackFrame;
    f32 mJumpSpeed;
    u32 mSmokeFrame;
    f32 mAttackBoundRate;
    f32 mAttackBoundMin;
    f32 mIdlingBoundRate;
    f32 mIdlingBoundMin;
    u32 _40;
    u32 mIdlingFrame;
};

}}}}  // namespace scn::step::enemy::needlous

#endif
