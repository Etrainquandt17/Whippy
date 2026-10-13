#ifndef SCN_STEP_GIMMICK_POPFLOWER_PARAM_H
#define SCN_STEP_GIMMICK_POPFLOWER_PARAM_H

#include "types.h"

namespace scn {
namespace step {
namespace gimmick {
namespace popflower {

// TODO: only the members scn/step/gimmick/popflower/PopFlower.cpp reads.
struct Param {
    f32 _0;
    f32 _4;
    f32 _8;
    u32 _C;
    f32 _10;
    u32 _14;
    f32 _18;
    u32 _1C[4];
    f32 _2C[4];
    f32 _3C[4];
};

}}}}  // namespace scn::step::gimmick::popflower

#endif
