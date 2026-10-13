#ifndef SCN_STEP_HERO_NEEDLEPARAM_H
#define SCN_STEP_HERO_NEEDLEPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names and the members around these. Param::needle() returns it; the sub-structs are what the
// states' file-local param() functions return.
struct NeedleParamAttackUp {
    u32 _0;
    u32 _4;
};

struct NeedleParamBurnAttack {
    u32 _0;
    u32 _4;
};

struct NeedleParamDash {
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
    f32 _14;
    f32 _18;
    u32 _1C;
};

struct NeedleParam {
    u32 _0[0xC];
    NeedleParamAttackUp _30;
    NeedleParamBurnAttack _38;
    f32 _40;
    f32 _44;
    NeedleParamDash _48;
    gobj::MoveParamFall _68;
};

}}}  // namespace scn::step::hero

#endif
