#ifndef SCN_STEP_ENEMY_SODORY_PARAMDATA_H
#define SCN_STEP_ENEMY_SODORY_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace sodory {

// TODO: the name is a guess: nothing in the game names what Param::sodory() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mSpeed[3];
    u32 _c[10];
    f32 mFlyOffsY;
    f32 mBodyOffsY;
    f32 mHeadOffsY;
    f32 mFlyShapeSize;
    u32 mMoveFrame;
};

}}}}  // namespace scn::step::enemy::sodory

#endif
