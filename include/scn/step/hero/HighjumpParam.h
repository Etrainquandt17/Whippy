#ifndef SCN_STEP_HERO_HIGHJUMPPARAM_H
#define SCN_STEP_HERO_HIGHJUMPPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names and the members around these. Param::highjump() returns it.
struct HighjumpParamJump {
    f32 _0;
    f32 _4;
    u32 _8;
    f32 _C;
    u32 _10;
    u32 _14;
    f32 _18;
    f32 _1C;
};

struct HighjumpParam {
    HighjumpParamJump _0[3];
    u32 _60;
    u32 _64;
    f32 _68;
    gobj::MoveParamAccel _6C;
    gobj::MoveParamDecel _78;
    f32 _7C;
    f32 _80;
    u32 _84;
    f32 _88;
    u32 _8C;
    u32 _90;
    f32 _94;
    f32 _98;
    u32 _9C;
    u32 _A0;
    f32 _A4;
    gobj::MoveParamAccel _A8;
    gobj::MoveParamDecel _B4;
    u32 _B8;
    u32 _BC;
    f32 _C0;
    f32 _C4;
    u32 _C8;
    gobj::MoveParamDecel _CC;
    gobj::MoveParamFall _D0;
    f32 _DC;
    f32 _E0;
    u32 _E4;
    u32 _E8;
    gobj::MoveParamDecel _EC;
    gobj::MoveParamFall _F0;
};

}
}
}

#endif
