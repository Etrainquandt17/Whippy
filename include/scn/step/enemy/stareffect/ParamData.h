#ifndef SCN_STEP_ENEMY_STAREFFECT_PARAMDATA_H
#define SCN_STEP_ENEMY_STAREFFECT_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace stareffect {

// TODO: the name is a guess: nothing in the game names what Param::stareffect() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mShapeWidth;
    f32 mShapeHeight;
    f32 mShapeOffset;
    u32 mScaleFrame;
    u32 mFlashFrame;
    u32 mLifeFrame[3];
    f32 mRotSpeed;
    f32 mPuffScale;
    gobj::MoveParamDecel mPuffDecel;
};

}}}}  // namespace scn::step::enemy::stareffect

#endif
