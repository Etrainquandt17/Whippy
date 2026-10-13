#ifndef SCN_STEP_HERO_STONEPARAM_H
#define SCN_STEP_HERO_STONEPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names. Param::stone() returns it.
struct StoneParamFallScrewStart {
    f32 _0;
    f32 _4;
    u32 _8;
};

struct StoneParamFall {
    f32 _0;
    f32 _4;
    f32 _8;
    u32 _C;
};

struct StoneParamSlip {
    gobj::MoveParamAccel _0;
    f32 _C;
    f32 _10;
};

struct StoneParamUpper {
    u32 _0;
    u32 _4;
};

struct StoneParam {
    f32 _0;
    f32 _4;
    int _8;
    int _C;
    f32 _10;
    f32 _14;
    f32 _18;
    StoneParamFallScrewStart _1C;
    StoneParamFall _28;
    u32 _38;
    StoneParamSlip _3C;
    f32 _50;
    f32 _54;
    u32 _58;
    StoneParamUpper _5C;
};

}}}  // namespace scn::step::hero

#endif
