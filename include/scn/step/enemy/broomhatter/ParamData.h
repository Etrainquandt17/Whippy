#ifndef SCN_STEP_ENEMY_BROOMHATTER_PARAMDATA_H
#define SCN_STEP_ENEMY_BROOMHATTER_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace broomhatter {

// TODO: the name is a guess: nothing in the game names what Param::broomhatter() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 _0[4];
    u32 mWalkAroundTurnCount;
    u32 mWalkEndFrame;
    u32 mWalkStartFrame;
    u32 mWalkEffectFrame;
    f32 mWalkDistance;
    f32 mWalkEffectOffsetY;
    hel::math::Vector3 mEscapeVelocity;
    gobj::MoveParamDecel mEscapeDecel;
    gobj::MoveParamFall mEscapeFall;
    f32 mEscapeVacuumOffHeight;
};

}}}}  // namespace scn::step::enemy::broomhatter

#endif
