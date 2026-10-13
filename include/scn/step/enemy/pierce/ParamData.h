#ifndef SCN_STEP_ENEMY_PIERCE_PARAMDATA_H
#define SCN_STEP_ENEMY_PIERCE_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace pierce {

// TODO: the name is a guess: nothing in the game names what Param::pierce() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 mAttackWaitFrame;
    u32 mAttackFrame;
    f32 mSinSpeedH;
    f32 mSinSpeedV;
    f32 mSinAngleSpeed;
    u32 _14[10];
    u32 mTurnFrame;
    f32 mAimFront;
    f32 mAimBack;
    f32 mAimV;
};

}
}
}
}

#endif
