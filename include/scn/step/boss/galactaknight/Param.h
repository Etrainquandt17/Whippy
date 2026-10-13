#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_PARAM_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_PARAM_H

#include "hel/math/Vec2.h"
#include "hel/math/Vec3.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

struct CollParam {
    f32 mBodyRadius;
    hel::math::Vec2 mBodyOffset;
    hel::math::Vec2 mBodyOffsetEnd;
    f32 mAttackRadius;
    hel::math::Vec2 mAttackOffset;
    hel::math::Vec2 mAttackOffsetEnd;
};

// TODO: the members are named after their offsets; the types are what the written states read.
struct Param {
    u32 _0;
    f32 _4;
    f32 _8;
    hel::math::Vec2 _C;
    hel::math::Vec2 _14;
    hel::math::Vec2 _1C;
    hel::math::Vec2 _24;
    u32 _2C;
    f32 _30;
    f32 _34;
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
    f32 _68;
    f32 _6C;
    f32 _70;
    f32 _74;
    f32 _78;
    f32 _7C;
    f32 _80;
    f32 _84;
    u32 _88;
    f32 _8C;
    f32 _90;
    f32 _94;
    f32 _98;
    f32 _9C;
    f32 _A0;
    f32 _A4;
    f32 _A8;
    f32 _AC;
    f32 _B0;
    f32 _B4;
    u32 _B8;
    f32 _BC;
    f32 _C0;
    f32 _C4;
    u32 _C8;
    u32 _CC;
    f32 _D0;
    f32 _D4;
    f32 _D8;
    f32 _DC;
    f32 _E0;
    u32 _E4;
    f32 _E8;
    f32 _EC;
    f32 _F0;
    u32 _F4;
    f32 _F8;
    u32 _FC;
    u32 _100;
    f32 _104;
    f32 _108;
    f32 _10C;
    f32 _110;
    f32 _114;
    f32 _118;
    f32 _11C;
    f32 _120;
    u32 _124;
    f32 _128;
    f32 _12C;
    u32 _130;
    f32 _134;
    u32 _138;
    f32 _13C;
    f32 _140;
    u32 _144;
    f32 _148;
    f32 _14C;
    hel::math::Vec3 _150;
    u32 _15C;
    u32 _160;
    f32 _164;
    f32 _168;
    f32 _16C;
    f32 _170;
    f32 _174;
    f32 _178;
    f32 _17C;
    f32 _180;
    CollParam mColl;
};

}
}
}
}

#endif
