#ifndef SCN_STEP_WEAPON_COMBINATIONDEDEDEBOMBER_PARAM_H
#define SCN_STEP_WEAPON_COMBINATIONDEDEDEBOMBER_PARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace combinationdededebomber {

// TODO: name the members.
struct LevelParam {
    f32 _0;
    f32 _4;
    f32 _8;
};

struct Param {
    LevelParam _0;
    LevelParam _C;
    LevelParam _18;
    u32 _24;
    f32 _28;
    f32 _2C;
    f32 _30;
    u32 _34;
    gobj::MoveParamDecel _38;
};

}}}}  // namespace scn::step::weapon::combinationdededebomber

#endif
