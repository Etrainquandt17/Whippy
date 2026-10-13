#ifndef SCN_STEP_HERO_COMMONPARAM_H
#define SCN_STEP_HERO_COMMONPARAM_H

#include "gobj/MoveParam.h"
#include "scn/step/hero/common/ParamReflectWall.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: name and members; the water states copy it whole.
struct CommonParamWater {
    gobj::MoveParamDecel _0;
    gobj::MoveParamAccel _4;
    gobj::MoveParamDecel _10;
    gobj::MoveParamAccel _14;
    gobj::MoveParamFall _20;
    gobj::MoveParamFall _2C;
    gobj::MoveParamFall _38;
    u32 _44[3];
};

// TODO: name; spear::StateFlight keeps one reference to it and reaches the three members from there.
struct CommonParamGround {
    gobj::MoveParamDecel _0;
    gobj::MoveParamAccel _4;
    gobj::MoveParamAccel _10;
};

// TODO: members.
struct CommonParam {
    // TODO: the members that a state reads, with padding between them, until the whole layout is known.
    union {
        u32 _0[0x137];
        struct {
            u32 _padG0[0x74 / 4];
            CommonParamGround _74g;
        };
        struct {
            u32 _padW0[0xA8 / 4];
            CommonParamWater _A8;
        };
        struct {
            u32 _padY0[0x18 / 4];
            u32 _18;
            u32 _padY1C[(0x2C - 0x1C) / 4];
            gobj::MoveParamDecel _2C;
            u32 _padY30[(0x3C - 0x30) / 4];
            gobj::MoveParamAccel _3C;
            u32 _padY48[(0xF4 - 0x48) / 4];
            f32 _F4;
            u32 _padYF8[(0x158 - 0xF8) / 4];
            f32 _158;
            u32 _padY15C;
            u32 _160;
            u32 _padY164[(0x1A4 - 0x164) / 4];
            f32 _1A4;
            u32 _1A8;
            u32 _1AC;
            gobj::MoveParamDecel _1B0;
            gobj::MoveParamDecel _1B4;
            u32 _padY1B8[(0x1C4 - 0x1B8) / 4];
            f32 _1C4;
            u32 _padY1C8[(0x3AC - 0x1C8) / 4];
            u32 _3AC;
            u32 _padY3B0[(0x47C - 0x3B0) / 4];
            common::ParamReflectWall _47C;
            common::ParamReflectWall _490;
        };
        struct {
            u32 _padX0[0x84 / 4];
            gobj::MoveParamAccel _84;
            u32 _padX90[(0x9C - 0x90) / 4];
            gobj::MoveParamFall _9C;
            u32 _padXA8[(0x164 - 0xA8) / 4];
            u32 _164;
            gobj::MoveParamFall _168;
            gobj::MoveParamFall _174;
            u32 _padX180[(0x228 - 0x180) / 4];
            u32 _228;
            f32 _22C;
            f32 _230;
            f32 _234;
            f32 _238;
            f32 _23C;
            f32 _240;
            f32 _244;
            f32 _248;
            u32 _padX24C[(0x254 - 0x24C) / 4];
            gobj::MoveParamAccel _254;
        };
        struct {
            u32 _pad0[0x74 / 4];
            gobj::MoveParamDecel _74;
            gobj::MoveParamAccel _78;
            u32 _pad84[(0x90 - 0x84) / 4];
            gobj::MoveParamFall _90;
            u32 _pad9C[(0xB8 - 0x9C) / 4];
            gobj::MoveParamDecel _B8;
            u32 _padBC[(0x180 - 0xBC) / 4];
            f32 _180;
            u32 _184;
            gobj::MoveParamFall _188;
            gobj::MoveParamFall _194;
            f32 _1A0;
            u32 _pad1A4[(0x1B8 - 0x1A4) / 4];
            f32 _1B8;
            f32 _1BC;
            gobj::MoveParamDecel _1C0;
        };
        struct {
            u32 _padR0[0x15C / 4];
            f32 _15C;
            u32 _padR160[(0x354 - 0x160) / 4];
            f32 _354;
            f32 _358;
            f32 _35C;
            u32 _360;
            f32 _364;
            u32 _padR368[(0x370 - 0x368) / 4];
            f32 _370;
            u32 _padR374[(0x3B0 - 0x374) / 4];
            f32 _3B0;
            u32 _padR3B4;
            f32 _3B8;
            f32 _3BC;
            f32 _3C0;
            u32 _3C4;
        };
    };
    f32 _4DC;
    f32 _4E0;
    f32 _4E4;
    f32 _4E8;
    f32 _4EC;
    f32 _4F0;
    f32 _4F4;
};

}}}  // namespace scn::step::hero

#endif
