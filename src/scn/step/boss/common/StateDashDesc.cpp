#include "scn/step/boss/common/StateDashDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

StateDashDesc::StateDashDesc(
    unsigned long a, gobj::MoveParamAccel accel, gobj::MoveParamDecel decel, gobj::MoveParamDecel decelEnd, gobj::MoveParamFall fall,
    hel::math::Vec2 b, hel::math::Vec2 c, hel::math::Vec2 d, bool e, hel::math::Vec2 f, hel::math::Vec2 g, GuardType guardType, bool h,
    ocoll::AttackType attackType
)
    : _0(a), _4(accel), _10(decel), _14(decelEnd), _18(fall), _24(b), _2C(c), _34(d), _3C(e), _40(f), _48(g), _50(guardType), _54(h),
      _58(attackType) {}

}
}
}
}
