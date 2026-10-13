#ifndef SCN_STEP_ENEMY_METALGENERALTHUNDER_PARAMDATA_H
#define SCN_STEP_ENEMY_METALGENERALTHUNDER_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec2.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralthunder {

// TODO: the name is a guess: nothing in the game names what Param::metalgeneralthunder() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    gobj::MoveParamDecel mDecel;
    gobj::MoveParamFall mFall;
    f32 mRotSpeed;
    u32 mAttackFrame;
    f32 mAttackRadius;
    hel::math::Vec2 mAttackOffset;
};

}
}
}
}

#endif
