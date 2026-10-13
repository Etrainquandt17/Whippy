#ifndef SCN_STEP_ENEMY_BARBAR_PARAMDATA_H
#define SCN_STEP_ENEMY_BARBAR_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace barbar {

// TODO: the name is a guess: nothing in the game names what Param::barbar() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 _0[4];
    f32 mStepBackDecel;
    u32 _14[14];
    f32 mHiddenSpeedRate;
    f32 mHiddenDecelRate;
};

}}}}  // namespace scn::step::enemy::barbar

#endif
