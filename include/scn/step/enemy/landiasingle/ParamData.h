#ifndef SCN_STEP_ENEMY_LANDIASINGLE_PARAMDATA_H
#define SCN_STEP_ENEMY_LANDIASINGLE_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec2.h"
#include "hel/math/Vec3.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace landiasingle {

// TODO: the name is a guess: nothing in the game names what Param::landiasingle() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 _0;
    hel::math::Vec2 _4;
    f32 _c;
    f32 _10;
    f32 _14;
    f32 _18;
    f32 _1c;
    f32 _20;
    f32 _24;
    f32 _28;
    f32 _2c;
    f32 _30;
    f32 _34;
    f32 _38;
    f32 _3c;
    u32 _40;
    u32 _44[28];
    u32 _b4;
    u32 _b8;
    u32 _bc[22];
    u32 mGrandCrossStopFrame;
    u32 _118[3];
    u32 _124;
    u32 _128[3];
    u32 _134;
    u32 _138;
    u32 _13c;
    u32 _140;
    u32 _144[18];
    f32 _18c;
    f32 _190;
    u32 _194[6];
    f32 mDeadEndOffsetY;
};

}
}
}
}

#endif
