#ifndef SCN_STEP_ENEMY_WADDLEDEE_PARAMDATA_H
#define SCN_STEP_ENEMY_WADDLEDEE_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledee {

// TODO: the name is a guess: nothing in the game names what Param::waddledee() returns.
struct ParamData {
    u32 mWhispyAppearFrame;
    f32 mWhispyAppearHeight;
    f32 mWhispyFallRotSpeed;
    gobj::MoveParamFall mWhispyFallFall;
    f32 mSmashedRotSpeed;
    gobj::MoveParamDecel mSmashedDecel;
    gobj::MoveParamFall mSmashedFall;
    u32 _2c;
    s32 mSmashedEndFrame;
    hel::math::Vector3 mGenerateVelocity[3];
    u32 mGenerateNum;
    f32 mGrandLowperAppearRotSpeed;
    f32 mGrandLowperAppearRotDecel;
    hel::math::Vector3 mEscapeVelocity;
    gobj::MoveParamDecel mEscapeDecel;
    gobj::MoveParamFall mEscapeFall;
    f32 mEscapeVacuumOffHeight;
};

}}}}  // namespace scn::step::enemy::waddledee

#endif
