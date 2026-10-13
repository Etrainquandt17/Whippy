#ifndef SCN_STEP_BOSS_GIGANTEDGE_PARAM_H
#define SCN_STEP_BOSS_GIGANTEDGE_PARAM_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec2.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace gigantedge {

// TODO: the name of the class is a guess; only what the script bindings read is known.
struct Param {
    u32 mHitPoint[3];
    f32 _C;
    f32 _10;
    f32 _14;
    f32 mBodyCollRadius;
    hel::math::Vec2 mBodyCollOffset;
    f32 mGuardCollRadius;
    hel::math::Vec2 mGuardCollOffset;
    hel::math::Vec2 mGuardCollOffset2;
    gobj::MoveParamDecel _38;
    gobj::MoveParamDecel _3C;
    gobj::MoveParamFall _40;
    hel::math::Vec2 _4C;
    hel::math::Vec2 _54;
    gobj::MoveParamAccel _5C;
    gobj::MoveParamAccel _68;
    u32 _74;
    gobj::MoveParamAccel _78;
    hel::math::Vec2 _84;
    hel::math::Vec2 _8C;
    hel::math::Vec2 _94;
    gobj::MoveParamDecel _9C;
    hel::math::Vec2 _A0;
    hel::math::Vec2 _A8;
    f32 _B0;
    f32 _B4;
    hel::math::Vec2 mSwordShotOffset;
    f32 mSwordShotSpeed;
    f32 mSwordShotAngle;
    hel::math::Vec2 _C8;
    gobj::MoveParamFall _D0;
};

}
}
}
}

#endif
