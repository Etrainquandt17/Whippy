#ifndef SCN_STEP_HERO_FIREPARAM_H
#define SCN_STEP_HERO_FIREPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names and the members around these. Param::fire() returns it.
struct FireParam {
    u32 _0[0x23];
    f32 _8C;
    f32 _90;
    f32 _94;
    u32 _98;
    f32 _9C;
    f32 _A0;
    gobj::MoveParamFall _A4;
    gobj::MoveParamDecel _B0;
    int _B4;
    u32 _B8[7];
    int _D4;
    int _D8;
    f32 _DC;
    f32 _E0;
    f32 _E4;
};

}
}
}

#endif
