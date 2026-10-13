#ifndef SCN_STEP_ENEMY_WALKY_PARAMDATA_H
#define SCN_STEP_ENEMY_WALKY_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace walky {

// TODO: the name is a guess: nothing in the game names what Param::walky() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mSpeed[3];
    u32 mJumpFrame;
    f32 mJumpSpeedH;
    f32 mJumpSpeedV;
    gobj::MoveParamDecel mJumpDecel;
    gobj::MoveParamFall mJumpFall;
    u32 mAttackWaitFrame;
    u32 mAttackShotFrame;
    u32 mAttackTurnFrame;
    u32 mAttackEndFrame;
};

}}}}  // namespace scn::step::enemy::walky

#endif
