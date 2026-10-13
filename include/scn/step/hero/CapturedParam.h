#ifndef SCN_STEP_HERO_CAPTUREDPARAM_H
#define SCN_STEP_HERO_CAPTUREDPARAM_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec2.h"
#include "hel/math/Vec3.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names, and the sizes are as far as the states read. Param::captured...() return these.
struct CapturedWhispyParam {
    u32 _0;
    u32 _4;
    f32 _8;
    f32 _C;
    gobj::MoveParamDecel _10;
    u32 _14;
    u32 _18;
    f32 _1C;
    f32 _20;
    f32 _24;
    f32 _28;
    u32 _2C;
    u32 _30;
    gobj::MoveParamDecel _34;
    gobj::MoveParamFall _38;
    f32 _44;
    u32 _48;
    u32 _4C;
    gobj::MoveParamDecel _50;
    u32 _54;
    f32 _58;
    f32 _5C;
    f32 _60;
    f32 _64;
    f32 _68;
    f32 _6C;
    u32 _70;
    u32 _74;
    gobj::MoveParamDecel _78;
    gobj::MoveParamFall _7C;
};

struct CapturedGrandLowperVomitParam {
    u32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    u32 _10;
    u32 _14;
    u32 _18;
    gobj::MoveParamDecel _1C;
    gobj::MoveParamFall _20;
};

struct CapturedGrandLowperParam {
    u32 _0;
    CapturedGrandLowperVomitParam _4;
    CapturedGrandLowperVomitParam _30;
};

struct CapturedFattyBufferParam {
    u32 _0;
    u32 _4;
    u32 _8;
    u32 _C;
    f32 _10;
    u32 _14;
    f32 _18;
    hel::math::Vec3 _1C;
    gobj::MoveParamDecel _28;
    gobj::MoveParamFall _2C;
    f32 _38;
    f32 _3C;
    u32 _40;
    u32 _44;
    u32 _48;
    u32 _4C;
};

struct CapturedDoubterShotPrepareParam {
    hel::math::Vec3 _0;
    hel::math::Vec3 _C;
    f32 _18;
};

struct CapturedDoubterParam {
    f32 _0;
    u32 _4;
    f32 _8;
    CapturedDoubterShotPrepareParam _C;
    f32 _28;
    f32 _2C;
    f32 _30;
    f32 _34;
    f32 _38;
    f32 _3C;
    u32 _40;
    f32 _44;
    f32 _48;
    f32 _4C;
    u32 _50;
    u32 _54;
    f32 _58;
    f32 _5C;
    f32 _60;
    f32 _64;
    u32 _68;
    u32 _6C;
    gobj::MoveParamDecel _70;
    gobj::MoveParamFall _74;
    f32 _80;
    f32 _84;
    f32 _88;
    f32 _8C;
    f32 _90;
    f32 _94;
    u32 _98;
    gobj::MoveParamDecel _9C;
    gobj::MoveParamFall _A0;
};

struct CapturedWaterGalborosParam {
    hel::math::Vec3 _0;
    gobj::MoveParamDecel _C;
    gobj::MoveParamFall _10;
    f32 _1C;
    u32 _20;
    u32 _24;
    u32 _28;
    u32 _2C;
};

struct CapturedHRD3Param {
    u32 _0;
    u32 _4;
    u32 _8;
    u32 _C;
    u32 _10;
    f32 _14;
    f32 _18;
    f32 _1C;
    f32 _20;
    f32 _24;
    u32 _28;
};

struct CapturedGalactaKnightParam {
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
    f32 _14;
    f32 _18;
    u32 _1C;
    f32 _20;
    u32 _24;
    f32 _28;
    int _2C;
    f32 _30;
    f32 _34;
    f32 _38;
    f32 _3C;
};

}}}  // namespace scn::step::hero

#endif
