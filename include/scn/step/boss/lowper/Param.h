#ifndef SCN_STEP_BOSS_LOWPER_PARAM_H
#define SCN_STEP_BOSS_LOWPER_PARAM_H

#include "hel/math/Vec2.h"
#include "hel/math/Vec3.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

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
    struct DynamicsNode {
        f32 _0;
        f32 _4;
        f32 _8;
        f32 _C;
        f32 _10;
        f32 _14;
        f32 _18;
        f32 _1C;
        f32 _20;
    };

    struct Dynamics {
        f32 _0;
        DynamicsNode mNodes[3];
    };

    u32 _0;
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
    f32 _2C;
    f32 _30;
    f32 _34;
    f32 _38;
    f32 _3C;
    u32 _40;
    f32 _44;
    u32 _48;
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
    u32 _74;
    f32 _78;
    f32 _7C;
    f32 _80;
    f32 _84;
    f32 _88;
    f32 _8C;
    f32 _90;
    f32 _94;
    CollParam _98;
    CollParam _C0;
    CollParam _E8;
    CollParam _110;
    Dynamics _138;
};

}}}}  // namespace scn::step::boss::lowper

#endif
