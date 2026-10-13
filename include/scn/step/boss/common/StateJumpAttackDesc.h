#ifndef SCN_STEP_BOSS_COMMON_STATEJUMPATTACKDESC_H
#define SCN_STEP_BOSS_COMMON_STATEJUMPATTACKDESC_H

#include "gobj/MoveParam.h"
#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

class StateJumpAttackDesc {
public:
    StateJumpAttackDesc(hel::math::Vector2, gobj::MoveParamDecel, gobj::MoveParamFall, int);

    hel::math::Vector2 _0;
    gobj::MoveParamDecel _8;
    gobj::MoveParamFall _C;
    int _18;
};

}}}}  // namespace scn::step::boss::common

#endif
