#ifndef SCN_STEP_ENEMY_FOLEY_PARAMDATA_H
#define SCN_STEP_ENEMY_FOLEY_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace foley {

// TODO: the name is a guess: nothing in the game names what Param::foley() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mWaitRangeV;
    f32 mMoveRangeV;
    f32 mRangeH;
    f32 mCameraMargin;
    u32 mAttackWaitFrame;
    u32 _14;
    f32 mAttackFrameRate;
    gobj::MoveParamAccel mMoveAccel[3];
    gobj::MoveParamFall mAttackFall;
    f32 mRotH;
    f32 mRotHDefault;
    f32 mWeaponOffsetX;
    f32 mBodyRadius;
};

}}}}  // namespace scn::step::enemy::foley

#endif
