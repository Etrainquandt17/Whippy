#ifndef SCN_STEP_HERO_DEEPARAM_H
#define SCN_STEP_HERO_DEEPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

namespace dee {

struct ParamWeapon {
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
};

}

// TODO: names. The layout is SpearParam's.
struct DeeParam {
    u32 _0;
    f32 _4;
    u32 _8;
    gobj::MoveParamAccel _C;
    gobj::MoveParamDecel _18;
    gobj::MoveParamFall _1C;
    f32 _28;
    u32 _2C;
    f32 _30;
    f32 _34;
    f32 _38;
    f32 _3C;
    gobj::MoveParamDecel _40;
    gobj::MoveParamFall _44;
    gobj::MoveParamDecel _50;
    f32 _54;
    dee::ParamWeapon _58;
    dee::ParamWeapon _68;
    dee::ParamWeapon _78;
    gobj::MoveParamDecel _88;
    gobj::MoveParamFall _8C;
    gobj::MoveParamDecel _98;
    f32 _9C;
    gobj::MoveParamFall _A0;
    u32 _AC;
    u32 _B0;
    gobj::MoveParamFall _B4;
    u32 _C0;
    f32 _C4;
    u32 _C8;
    u32 _CC;
    u32 _D0;
    f32 _D4;
    f32 _D8;
    f32 _DC;
    f32 _E0;
    f32 _E4;
    f32 _E8;
    f32 _EC;
    f32 _F0;
    gobj::MoveParamFall _F4;
    f32 _100;
};

}}}  // namespace scn::step::hero

#endif
