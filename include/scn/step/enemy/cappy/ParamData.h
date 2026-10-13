#ifndef SCN_STEP_ENEMY_CAPPY_PARAMDATA_H
#define SCN_STEP_ENEMY_CAPPY_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace cappy {

// TODO: the name is a guess: nothing in the game names what Param::cappy() returns.
struct ParamData {
    u32 mAttackStopFrame;
    u32 mAttackStopLength;
    u32 mAttackThrowFrame;
    f32 mHatOffsetY;
    f32 mHatSpeedV;
    s32 mSearchHatFrame;
    f32 mSkinnedSpeedH;
    f32 mSkinnedSpeedV;
    u32 _20[2];
    gobj::MoveParamDecel mDecel;
    gobj::MoveParamFall mFall;
};

}}}}  // namespace scn::step::enemy::cappy

#endif
