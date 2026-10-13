#ifndef SCN_STEP_ENEMY_CRABY_PARAMDATA_H
#define SCN_STEP_ENEMY_CRABY_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace craby {

// TODO: the name is a guess: nothing in the game names what Param::craby() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 mAimWaitFrame;
    f32 mAimRangeV;
    f32 mAimRangeH;
    gobj::MoveParamAccel mWalkAccel[4];
    f32 mWalkSpeedBase;
    f32 mAroundDist;
    f32 mAroundRange;
};

}}}}  // namespace scn::step::enemy::craby

#endif
