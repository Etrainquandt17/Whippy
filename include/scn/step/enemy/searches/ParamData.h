#ifndef SCN_STEP_ENEMY_SEARCHES_PARAMDATA_H
#define SCN_STEP_ENEMY_SEARCHES_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace searches {

// TODO: the name is a guess: nothing in the game names what Param::searches() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mSpeed;
    u32 mMoveFrame;
    f32 mAttackRange;
    u32 mWaitFrame;
    u32 mAttackFrame;
    u32 mDeadFrame;
};

}}}}  // namespace scn::step::enemy::searches

#endif
