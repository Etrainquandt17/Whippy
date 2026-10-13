#ifndef SCN_STEP_WEAPON_NINJAKUNAI_PARAM_H
#define SCN_STEP_WEAPON_NINJAKUNAI_PARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace ninjakunai {

// TODO: name the members; the ones not seen in use yet are taken to be words.
struct Param {
    struct Vanish {
        f32 _0;
        f32 _4;
        f32 _8;
        f32 _C;
        f32 _10;
        gobj::MoveParamDecel _14;
        gobj::MoveParamFall _18;
        u32 _24;
    };

    f32 _0;
    u32 _4;
    u32 _8;
    u32 _C;
    f32 _10;
    f32 _14;
    f32 _18;
    f32 _1C;
    f32 _20;
    f32 _24;
    f32 _28;
    Vanish _2C;
    Vanish _54;
    f32 _7C;
    f32 _80;
    f32 _84;
};

}}}}  // namespace scn::step::weapon::ninjakunai

#endif
