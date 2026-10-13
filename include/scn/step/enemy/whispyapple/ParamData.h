#ifndef SCN_STEP_ENEMY_WHISPYAPPLE_PARAMDATA_H
#define SCN_STEP_ENEMY_WHISPYAPPLE_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec3.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace whispyapple {

// TODO: the name is a guess: nothing in the game names what Param::whispyapple() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    gobj::MoveParamDecel mDecel;
    f32 mFallAccel;
    f32 mFallResist;
    f32 mBound1SpeedV;
    f32 mBound1FallAccel;
    f32 mBound1RotSpeed;
    f32 mBound1FallAccelDecel;
    f32 mBound1FallSpeed;
    f32 mBound1FallAccelDown;
    f32 mBound1FallResist;
    gobj::MoveParamAccel mBound1Accel;
    f32 mBound2SpeedV;
    f32 mBound2SpeedH;
    f32 mBound2RotSpeed;
    gobj::MoveParamFall mBound2Fall;
    hel::math::Vec3 mNearVelocity;
    hel::math::Vec3 mNearVelocityFar;
    f32 mNearRotSpeed;
    f32 mNearRotXSpeed;
    f32 mNearInvalidZ;
    f32 mNearBoundZ;
    f32 mNearRandMin;
    f32 mNearRandMax;
    gobj::MoveParamFall mNearFall;
};

}
}
}
}

#endif
