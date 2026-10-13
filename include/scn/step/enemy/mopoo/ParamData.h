#ifndef SCN_STEP_ENEMY_MOPOO_PARAMDATA_H
#define SCN_STEP_ENEMY_MOPOO_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mopoo {

// TODO: the name is a guess: nothing in the game names what Param::mopoo() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    int mHideWaitTime;
    f32 mRangeLeft;
    f32 mRangeRight;
    f32 mRangeTop;
    f32 mRangeBottom;
};

}}}}  // namespace scn::step::enemy::mopoo

#endif
