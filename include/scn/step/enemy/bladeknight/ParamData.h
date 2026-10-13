#ifndef SCN_STEP_ENEMY_BLADEKNIGHT_PARAMDATA_H
#define SCN_STEP_ENEMY_BLADEKNIGHT_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace bladeknight {

// TODO: the name is a guess: nothing in the game names what Param::bladeknight() returns.
struct ParamData {
    u32 mAttackMoveFrame;
    u32 mAttackBackFrame;
    f32 mAttackSpeed;
    u32 mDoubleAttackMoveFrame1;
    u32 mDoubleAttackMoveFrame2;
    u32 _14;
    f32 mDoubleAttackSpeed;
    f32 mDoubleAttackStopFrame;
    u32 mDoubleAttackStopCount;
    f32 mStepBackSpeed;
    f32 mStepBackDecelFrame;
    gobj::MoveParamDecel mStepBackDecel;
    hel::math::Vector3 mEscapeVelocity;
    gobj::MoveParamDecel mEscapeDecel;
    gobj::MoveParamFall mEscapeFall;
    f32 mEscapeVacuumOffHeight;
};

}}}}  // namespace scn::step::enemy::bladeknight

#endif
