#ifndef SCN_STEP_BOSS_COMMON_STATEATTACKDESC_H
#define SCN_STEP_BOSS_COMMON_STATEATTACKDESC_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec2.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

class StateAttackDesc {
public:
    StateAttackDesc(gobj::MoveParamDecel, hel::math::Vec2, hel::math::Vec2, f32, f32);

    gobj::MoveParamDecel _0;
    hel::math::Vec2 _4;
    hel::math::Vec2 _C;
    f32 _14;
    f32 _18;
};

}}}}  // namespace scn::step::boss::common

#endif
