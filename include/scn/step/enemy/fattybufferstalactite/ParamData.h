#ifndef SCN_STEP_ENEMY_FATTYBUFFERSTALACTITE_PARAMDATA_H
#define SCN_STEP_ENEMY_FATTYBUFFERSTALACTITE_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace fattybufferstalactite {

// TODO: the name is a guess: nothing in the game names what Param::fattybufferstalactite() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mAppearStep;
    f32 mEffectOffsetY;
    f32 mRotSpeed;
    gobj::MoveParamDecel mDecel;
    gobj::MoveParamFall mFall;
    u32 mLandFrameBase;
    u32 mLandFrameRand;
    u32 mShakeStartFrame;
    u32 mShakeInterval;
};

}}}}  // namespace scn::step::enemy::fattybufferstalactite

#endif
