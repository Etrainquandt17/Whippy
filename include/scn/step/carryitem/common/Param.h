#ifndef SCN_STEP_CARRYITEM_COMMON_PARAM_H
#define SCN_STEP_CARRYITEM_COMMON_PARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace carryitem {
namespace common {

// TODO: name the members; the ones not seen in use yet are taken to be words.
struct UseParam {
    f32 _0;
    gobj::MoveParamDecel _4;
    gobj::MoveParamFall _8;
    f32 _14;
    f32 _18;
    f32 _1C;
    f32 _20;
};

struct FallParam {
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
    f32 _14;
    f32 _18;
    f32 _1C;
    gobj::MoveParamDecel _20;
    gobj::MoveParamFall _24;
    gobj::MoveParamDecel _30;
    gobj::MoveParamFall _34;
    f32 _40;
    f32 _44;
    f32 _48;
    f32 _4C;
    f32 _50;
};

struct Param {
    u32 _0;
    u32 _4;
    UseParam mUse;
    FallParam mFall;
    u32 _80;
    u32 _84;
    u32 _88;
};

}}}}  // namespace scn::step::carryitem::common

#endif
