#ifndef SCN_STEP_ENEMY_TOGEKUKI_PARAMDATA_H
#define SCN_STEP_ENEMY_TOGEKUKI_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace togekuki {

// TODO: the name is a guess: nothing in the game names what Param::togekuki() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 mTurnFrame;
    gobj::MoveParamDecel mDecel;
    gobj::MoveParamFall mFall;
};

}}}}  // namespace scn::step::enemy::togekuki

#endif
