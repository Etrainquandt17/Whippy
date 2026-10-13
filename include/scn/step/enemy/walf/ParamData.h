#ifndef SCN_STEP_ENEMY_WALF_PARAMDATA_H
#define SCN_STEP_ENEMY_WALF_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace walf {

// TODO: the name is a guess: nothing in the game names what Param::walf() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 _0[7];
    hel::math::Vector2 mInWaterWallOffset;
    u32 mInWaterJumpFrame;
    u32 mInWaterFrame;
    f32 mInWaterSpeedH;
    f32 mInWaterSpeedV;
    gobj::MoveParamAccel mGroundAccel;
    u32 mFallInWaterFrame;
    gobj::MoveParamFall mFall;
    gobj::MoveParamDecel mWaterDecel;
    u32 _54[11];
    hel::math::Vector2 mInWaterOffset;
    hel::math::Vector2 mFloatingOffset;
};

}}}}  // namespace scn::step::enemy::walf

#endif
