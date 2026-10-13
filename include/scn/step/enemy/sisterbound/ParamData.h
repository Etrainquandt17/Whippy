#ifndef SCN_STEP_ENEMY_SISTERBOUND_PARAMDATA_H
#define SCN_STEP_ENEMY_SISTERBOUND_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace sisterbound {

// TODO: the name is a guess: nothing in the game names what Param::sisterbound() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    gobj::MoveParamFall mFall;
    f32 mFallAccel;
    gobj::MoveParamFall mJumpFall;
    int mJumpFrame;
    f32 mJumpSpeed;
    f32 mLandingFrameRate;
    f32 mBodyRadius;
    f32 mHeadRadius;
    hel::math::Vector2 mBodyOffset;
    hel::math::Vector2 mHeadOffset;
    hel::math::Vector2 mHeadOffset2;
};

}
}
}
}

#endif
