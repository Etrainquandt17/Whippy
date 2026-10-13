#ifndef SCN_STEP_ENEMY_CHILLY_PARAMDATA_H
#define SCN_STEP_ENEMY_CHILLY_PARAMDATA_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace chilly {

// TODO: the name is a guess: nothing in the game names what Param::chilly() returns.
struct ParamData {
    u32 mMoveReversePercent;
    u32 mMoveStartFrame;
    f32 mMoveDistance;
    u32 mAttackEndFrame;
    u32 mAttackScriptFrame;
    u32 mAttackEffectFrame;
    u32 mAttackCollFrame;
    u32 mMoveTurnFrame;
    f32 mAttackRadius;
    hel::math::Vector2 mAttackOffset;
};

}
}
}
}

#endif
