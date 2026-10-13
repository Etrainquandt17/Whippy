#ifndef SCN_STEP_ENEMY_JUCKLE_PARAMDATA_H
#define SCN_STEP_ENEMY_JUCKLE_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace juckle {

// TODO: the name is a guess: nothing in the game names what Param::juckle() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 mShotFrame;
    f32 mShotFrameRate;
    u32 _8;
    f32 mNearAngle;
    f32 mFarAngle;
    f32 mRot[8];
    f32 mAnger[8];
};

}}}}  // namespace scn::step::enemy::juckle

#endif
