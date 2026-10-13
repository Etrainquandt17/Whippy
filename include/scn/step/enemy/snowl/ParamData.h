#ifndef SCN_STEP_ENEMY_SNOWL_PARAMDATA_H
#define SCN_STEP_ENEMY_SNOWL_PARAMDATA_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace snowl {

// TODO: the name is a guess: nothing in the game names what Param::snowl() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 _0[7];
    hel::math::Vector2 mBallVelocity;
};

}
}
}
}

#endif
