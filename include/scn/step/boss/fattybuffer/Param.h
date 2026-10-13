#ifndef SCN_STEP_BOSS_FATTYBUFFER_PARAM_H
#define SCN_STEP_BOSS_FATTYBUFFER_PARAM_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec2.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

// TODO: the name of the class is a guess, and so are the types of the members no unit reads.
struct StampParam {
    u32 mRiseFrame;
    f32 mRiseHeight;
    u32 mHoldFrame;
    f32 mHoldHeight;
    u32 mFallFrame;
    f32 mChaseSpeedMax;
    f32 mChaseAccel;
};

struct Param {
    u32 mHitPoint;
    u32 mHitPointExtra;
    f32 mAngryHpRate;
    f32 mAngryHpRateExtra;
    f32 mScaleDefault;
    gobj::MoveParamDecel _14;
    gobj::MoveParamDecel _18;
    gobj::MoveParamFall _1C;
    hel::math::Vec2 _28;
    hel::math::Vec2 _30;
    f32 _38;
    f32 _3C;
    f32 _40;
    f32 _44;
    f32 _48;
    f32 _4C;
    f32 _50;
    f32 _54;
    f32 _58;
    f32 _5C;
    f32 _60;
    f32 _64;
    u32 _68;
    f32 _6C;
    f32 _70;
    f32 _74;
    gobj::MoveParamDecel _78;
    u32 _7C;
    u32 _80;
    f32 _84;
    u32 _88;
    f32 _8C;
    u32 _90;
    u32 _94;
    u32 _98;
    f32 _9C;
    u32 _A0;
    f32 _A4;
    f32 _A8;
    f32 _AC;
    f32 _B0;
    f32 _B4;
    u32 _B8;
    u32 _BC;
    u32 _C0;
    u32 _C4;
    u32 _C8;
    u32 _CC;
    f32 _D0;
    u32 _D4;
    u32 _D8;
    u32 _DC;
    u32 _E0;
    u32 _E4;
    u32 _E8;
    u32 _EC;
    u32 _F0;
    u32 _F4;
    u32 _F8;
    u32 _FC;
    u32 _100;
    f32 _104;
    f32 _108;
    hel::math::Vec2 _10C;
    hel::math::Vec2 _114;
    f32 _11C;
    f32 _120;
    f32 _124;
    f32 _128;
    u32 _12C;
    u32 _130;
    f32 _134;
    f32 _138;
    f32 _13C;
    gobj::MoveParamFall _140;
    f32 _14C;
    gobj::MoveParamFall _150;
    f32 _15C;
    gobj::MoveParamFall _160;
    StampParam mStamp;
    StampParam mStampAngry;
    f32 _1A4;
    f32 mScaleAnger;
    u32 mAngerScaleTime;
};

}
}
}
}

#endif
