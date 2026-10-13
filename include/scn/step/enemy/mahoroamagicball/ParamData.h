#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_PARAMDATA_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

// TODO: the names are guesses: nothing in the game names what Param::mahoroamagicball() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    struct NWay {
        u32 mInterval;
        f32 mSpeed;
    };

    struct Follow {
        f32 mOffsetY;
        f32 mAngleSpeed;
        f32 mRadiusSpeed;
        f32 mRadiusMax;
    };

    u32 _0[14];
    f32 m6WaySpeed;
    f32 m6WaySpeedExtra;
    Follow mHoming;
    Follow mHomingExtra;
    u32 _60[8];
    NWay mNWay;
    NWay mNWayExtra;
    u32 _90[2];
    f32 mSharpshootSpeed;
    f32 mSharpshootSpeedExtra;
};

}
}
}
}

#endif
