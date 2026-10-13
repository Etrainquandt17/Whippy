#ifndef SCN_STEP_ENEMY_COMMON_PARAMDATA_H
#define SCN_STEP_ENEMY_COMMON_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

// TODO: the name is a guess: nothing in the game names what Param::common() returns.
struct ParamData {
    gobj::MoveParamDecel mDecel;
    gobj::MoveParamFall mFall;
    gobj::MoveParamFall mFallWater;
    u32 mFlushFrame;
    f32 mFlushHeight;
    u32 mFlushWait;
    u32 _28[9];
    gobj::MoveParamDecel _4c;
    u32 _50[14];
    f32 mCliffFrontDist;
};

}}}}  // namespace scn::step::enemy::common

#endif
