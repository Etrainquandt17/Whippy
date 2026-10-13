#ifndef SCN_STEP_ITEM_PARAM_H
#define SCN_STEP_ITEM_PARAM_H

#include "types.h"

namespace scn {
namespace step {
namespace item {

// TODO: name the members; the ones not seen in use yet are taken to be words.
struct Param {
    u32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
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
    f32 _40;
    f32 _44;
    f32 _48;
    f32 _4C;
    f32 _50;
    f32 _54;
    f32 _58;
    f32 _5C;
    f32 _60;
    f32 _64;
    u32 _68[28];
    u32 _D8;
    u32 _DC;
    u32 _E0;
    f32 _E4;
    u32 _E8;
    f32 _EC;
    u32 _F0[9];
    f32 _114;
    u32 _118;
    f32 _11C;
    f32 _120;
    f32 _124;
};

}}}  // namespace scn::step::item

#endif
