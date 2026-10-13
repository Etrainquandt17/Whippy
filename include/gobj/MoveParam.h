#ifndef GOBJ_MOVEPARAM_H
#define GOBJ_MOVEPARAM_H

#include "types.h"

namespace gobj {

// TODO: name the members.
struct MoveParamAccel {
    static MoveParamAccel Zero();
    static MoveParamAccel Create(f32 _0, f32 _4, f32 _8);

    f32 _0;
    f32 _4;
    f32 _8;
};

struct MoveParamDecel {
    static MoveParamDecel Zero();
    static MoveParamDecel Create(f32 _0);

    f32 _0;
};

struct MoveParamFall {
    static MoveParamFall Zero();
    static MoveParamFall Create(f32 _0, f32 _4, f32 _8);

    f32 _0;
    f32 _4;
    f32 _8;
};

}

#endif
