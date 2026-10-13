#ifndef SCN_STEP_ENEMY_DEGOUT_PARAMDATA_H
#define SCN_STEP_ENEMY_DEGOUT_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace degout {

// TODO: the name is a guess: nothing in the game names what Param::degout() returns. The members named after
// their offsets and whatever follows the last one are not known yet.
struct ParamData {
    u32 _0[3];
    f32 mChaseAccelLv0;
    f32 mChaseSpeedMaxLv0;
    f32 mChaseAccelLv1;
    f32 mChaseSpeedMaxLv1;
    f32 mChaseAccelLv2;
    f32 mChaseSpeedMaxLv2;
    u32 mChaseFrameLv0;
    u32 mChaseFrameLv1;
    u32 mChaseFrameLv2;
    u32 mFirstChaseStartFrame;
    u32 mFirstChaseShakeFrame;
    f32 mFirstChaseShakeWidth;
    u32 _3c[7];
    f32 mChaseTargetOffsetY;
};

}
}
}
}

#endif
