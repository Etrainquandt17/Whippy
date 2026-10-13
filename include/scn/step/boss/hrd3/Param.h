#ifndef SCN_STEP_BOSS_HRD3_PARAM_H
#define SCN_STEP_BOSS_HRD3_PARAM_H

#include "hel/math/Vec2.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

// TODO: only the members that the written states read are named.
struct Param {
    u32 _0[(0xC - 0x0) / 4];
    f32 _C;
    u32 _10;
    hel::math::Vec2 _14;
    hel::math::Vec2 _1C;
    hel::math::Vec2 _24;
    f32 _2C;
    f32 _30;
    f32 _34;
    f32 _38;
    u32 _3C;
    u32 _40[(0x4C - 0x40) / 4];
    u32 _4C;
    u32 _50;
    u32 _54;
    f32 _58;
    u32 _5C[(0x9C - 0x5C) / 4];
    u32 _9C;
    f32 _A0;
    f32 _A4;
    u32 _A8;
    f32 _AC;
    f32 _B0;
    f32 _B4;
    f32 _B8;
    u32 _BC;
    f32 _C0;
    f32 _C4;
    u32 _C8[(0xD4 - 0xC8) / 4];
    u32 _D4;
    u32 _D8;
    f32 _DC;
    f32 _E0;
    u32 _E4;
    f32 _E8;
    u32 _EC;
    f32 _F0;
    f32 _F4;
    f32 _F8;
    f32 _FC;
    f32 _100;
    u32 _104[(0x128 - 0x104) / 4];
    f32 _128;
    f32 _12C;
    f32 _130;
    f32 _134;
    f32 _138;
};

}
}
}
}

#endif
