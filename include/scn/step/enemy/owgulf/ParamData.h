#ifndef SCN_STEP_ENEMY_OWGULF_PARAMDATA_H
#define SCN_STEP_ENEMY_OWGULF_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace owgulf {

// TODO: the name is a guess: nothing in the game names what Param::owgulf() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mAroundDist;
    f32 m1WayAngle;
    f32 m3WayAngle[3];
    f32 m3WaySpeed;
    f32 mSpeed;
    u32 _1c;
    u32 m1WayFrame;
    u32 m3WayFrame;
};

}
}
}
}

#endif
