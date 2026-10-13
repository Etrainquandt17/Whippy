#ifndef SCN_STEP_BOSS_MOUNDEATH_PARAM_H
#define SCN_STEP_BOSS_MOUNDEATH_PARAM_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec2.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

struct Param {
    u32 mHitPoint[3];
    f32 _C;
    f32 _10;
    f32 _14;
    f32 mBodyCollRadius;
    hel::math::Vec2 mBodyCollOffset;
    gobj::MoveParamDecel _24;
    gobj::MoveParamDecel _28;
    gobj::MoveParamFall _2C;
    gobj::MoveParamFall _38;
    hel::math::Vec2 _44;
    hel::math::Vec2 _4C;
    f32 _54;
    f32 _58;
    f32 _5C;
    u32 _60;
    hel::math::Vec2 _64;
    hel::math::Vec2 _6C;
    u32 _74;
    f32 _78;
    f32 _7C;
    u32 _80;
    f32 _84;
    u32 _88;
    f32 _8C;
    u32 _90;
    f32 _94;
    u32 _98;
    f32 _9C;
    u32 _A0;
    f32 _A4;
    u32 _A8;
    f32 _AC;
    f32 _B0;
    u32 _B4;
    f32 _B8;
    u32 _BC;
    f32 _C0;
    u32 _C4;
    u32 _C8;
    f32 _CC;
    f32 _D0;
    u32 _D4;
    gobj::MoveParamAccel _D8;
    hel::math::Vec2 _E4;
    hel::math::Vec2 _EC;
    hel::math::Vec2 _F4;
    u32 _FC;
    u32 _100;
    gobj::MoveParamAccel _104;
    u32 _110;
    u32 _114;
    gobj::MoveParamAccel _118;
    f32 _124;
    u32 _128;
    gobj::MoveParamDecel _12C;
    f32 _130;
    f32 _134;
    gobj::MoveParamDecel _138;
    f32 _13C;
    u32 _140;
    f32 _144;
    u32 _148;
    f32 _14C;
    f32 _150;
    f32 _154;
    f32 _158;
    f32 _15C;
    gobj::MoveParamAccel _160;
    u32 _16C;
};

}
}
}
}

#endif
