#include "scn/step/boss/common/StateJump.h"

#include "mintglue/VectorInline.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

StateJumpDesc::StateJumpDesc(
    hel::math::Vector2 speed, gobj::MoveParamDecel a, gobj::MoveParamDecel decel, gobj::MoveParamFall fall, hel::math::Vector2 starPos,
    hel::math::Vector2 starSpeed, bool isTurn, LandingAnimType landingAnimType, bool isStar, ocoll::AttackType attackType
)
    : _0(speed), _8(a), _C(decel), _10(fall), _1C(starPos), _24(starSpeed), _2C(isTurn), _30(landingAnimType), _34(isStar),
      _38(attackType) {}

}}}}  // namespace scn::step::boss::common
