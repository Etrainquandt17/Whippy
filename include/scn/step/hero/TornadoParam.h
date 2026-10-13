#ifndef SCN_STEP_HERO_TORNADOPARAM_H
#define SCN_STEP_HERO_TORNADOPARAM_H

#include "gobj/MoveParam.h"
#include "scn/step/hero/tornado/ParamTornadoMove.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names and the members behind 0x124. Param::tornado() returns it.
struct TornadoParam {
    gobj::MoveParamAccel _0;
    tornado::ParamTornadoMove _C;
    tornado::ParamTornadoMove _30;
    f32 _54;
    f32 _58;
    f32 _5C;
    gobj::MoveParamAccel _60;
    gobj::MoveParamDecel _6C;
    gobj::MoveParamFall _70;
    u32 _7C;
    f32 _80;
    u32 _84;
    f32 _88;
    u32 _8C;
    int _90;
    int _94;
    int _98;
    u32 _9C;
    int _A0;
    int _A4;
    f32 _A8;
    f32 _AC;
    f32 _B0;
    u32 _B4;
    gobj::MoveParamDecel _B8;
    gobj::MoveParamDecel _BC;
    u32 _C0[3];
    u32 _CC;
    u32 _D0;
    f32 _D4;
    f32 _D8;
    f32 _DC;
    f32 _E0;
    f32 _E4;
    f32 _E8;
    gobj::MoveParamAccel _EC;
    gobj::MoveParamDecel _F8;
    gobj::MoveParamFall _FC;
    gobj::MoveParamAccel _108;
    gobj::MoveParamDecel _114;
    gobj::MoveParamFall _118;
};

}}}  // namespace scn::step::hero

#endif
