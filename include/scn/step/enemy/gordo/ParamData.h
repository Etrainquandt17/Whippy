#ifndef SCN_STEP_ENEMY_GORDO_PARAMDATA_H
#define SCN_STEP_ENEMY_GORDO_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace gordo {

// TODO: the name is a guess: nothing in the game names what Param::gordo() returns. Whatever follows the last
// member is not known yet.
struct ParamData {
    f32 mCircleSpeedLv0;
    f32 mCircleSpeedLv1;
    f32 mCircleSpeedLv2;
    f32 mCircleRadius;
    f32 mCircleRadiusMiddle;
    f32 mCircleRadiusLarge;
    f32 mStraightSpeed;
    f32 mBigCullingSize;
    f32 mBigCullingMargin;
};

}}}}  // namespace scn::step::enemy::gordo

#endif
