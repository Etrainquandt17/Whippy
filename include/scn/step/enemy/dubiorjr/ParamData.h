#ifndef SCN_STEP_ENEMY_DUBIORJR_PARAMDATA_H
#define SCN_STEP_ENEMY_DUBIORJR_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace dubiorjr {

// TODO: the name is a guess: nothing in the game names what Param::dubiorjr() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    gobj::MoveParamDecel mDecel;
    f32 _4;
    u32 _8;
    u32 _c;
    f32 _10;
    f32 mBackSpeed;
    gobj::MoveParamDecel mBackDecel;
};

}}}}  // namespace scn::step::enemy::dubiorjr

#endif
