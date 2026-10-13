#ifndef SCN_STEP_BOSS_DOUBTER_PARAM_H
#define SCN_STEP_BOSS_DOUBTER_PARAM_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec2.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

// TODO: the name of the class is a guess, and so are the types of the members no unit reads.
struct PunchParam {
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
    f32 _14;
};

struct TornadoChaseParam {
    f32 _0;
    f32 _4;
    f32 _8;
    gobj::MoveParamAccel _C;
};

struct Param {
    u32 mHitPoint;
    u32 mHitPointExtra;
    f32 mAngryHpRate;
    f32 mAngryHpRateExtra;
    gobj::MoveParamDecel _10;
    gobj::MoveParamDecel _14;
    gobj::MoveParamFall _18;
    hel::math::Vec2 _24;
    hel::math::Vec2 _2C;
    u32 _34;
    u32 _38;
    u32 _3C;
    u32 _40;
    f32 _44;
    f32 _48;
    f32 _4C;
    f32 _50;
    f32 _54;
    f32 _58;
    f32 _5C;
    f32 _60;
    f32 _64;
    gobj::MoveParamFall _68;
    gobj::MoveParamFall _74;
    u32 _80;
    u32 _84;
    f32 _88;
    f32 _8C;
    gobj::MoveParamDecel _90;
    gobj::MoveParamFall _94;
    gobj::MoveParamFall _A0;
    f32 _AC;
    gobj::MoveParamAccel _B0;
    gobj::MoveParamFall _BC;
    f32 _C8;
    TornadoChaseParam mTornadoChase;
    TornadoChaseParam mTornadoChaseExtra;
    hel::math::Vec2 _FC;
    f32 _104;
    f32 _108;
    f32 _10C;
    f32 _110;
    PunchParam mPunch;
    PunchParam mPunchExtra;
    u32 _144;
    u32 _148;
    u32 _14C;
    u32 _150;
    f32 _154;
    f32 _158;
    gobj::MoveParamDecel _15C;
    gobj::MoveParamFall _160;
    gobj::MoveParamDecel _16C;
    gobj::MoveParamFall _170;
    f32 mScaleAnger;
    f32 mAngerScaleRate;
    u32 _184;
    u32 _188;
    u32 _18C;
    u32 _190;
    f32 _194;
    f32 _198;
    f32 _19C;
    f32 _1A0;
    f32 _1A4;
    f32 _1A8;
    f32 _1AC;
};

}}}}  // namespace scn::step::boss::doubter

#endif
