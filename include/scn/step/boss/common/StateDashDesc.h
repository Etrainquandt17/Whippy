#ifndef SCN_STEP_BOSS_COMMON_STATEDASHDESC_H
#define SCN_STEP_BOSS_COMMON_STATEDASHDESC_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec2.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/ocoll/AttackType.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

class StateDashDesc {
public:
    StateDashDesc(
        unsigned long, gobj::MoveParamAccel, gobj::MoveParamDecel, gobj::MoveParamDecel, gobj::MoveParamFall, hel::math::Vec2,
        hel::math::Vec2, hel::math::Vec2, bool, hel::math::Vec2, hel::math::Vec2, GuardType, bool, ocoll::AttackType
    );

    u32 _0;
    gobj::MoveParamAccel _4;
    gobj::MoveParamDecel _10;
    gobj::MoveParamDecel _14;
    gobj::MoveParamFall _18;
    hel::math::Vec2 _24;
    hel::math::Vec2 _2C;
    hel::math::Vec2 _34;
    bool _3C;
    hel::math::Vec2 _40;
    hel::math::Vec2 _48;
    GuardType _50;
    bool _54;
    ocoll::AttackType _58;
};

}
}
}
}

#endif
