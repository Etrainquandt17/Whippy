#ifndef SCN_STEP_HERO_SPARKPARAM_H
#define SCN_STEP_HERO_SPARKPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names and the members behind these. Param::spark() returns it.
struct SparkParamAttack {
    u32 _0;
    u32 _4;
    u32 _8;
};

struct SparkParamAttackOver {
    u32 _0;
    u32 _4;
    u32 _8;
    u32 _C;
};

struct SparkParamAttackUnder {
    u32 _0;
    u32 _4;
    u32 _8;
    u32 _C;
};

struct SparkParamShot {
    u32 _0;
    u32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
    gobj::MoveParamDecel _14;
    gobj::MoveParamFall _18;
};

struct SparkParam {
    SparkParamAttack _0;
    SparkParamAttackOver _C;
    SparkParamAttackUnder _1C;
    u32 _2C;
    u32 _30;
    u32 _34;
    u32 _38[(0x8C - 0x38) / 4];
    SparkParamShot _8C;
    SparkParamShot _B0;
    SparkParamShot _D4;
};

}}}  // namespace scn::step::hero

#endif
