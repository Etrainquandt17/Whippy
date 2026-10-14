#include "scn/step/boss/common/StateJumpAttackDesc.h"

#include "mintglue/VectorInline.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace common {

StateJumpAttackDesc::StateJumpAttackDesc(Vector2 speed, gobj::MoveParamDecel decel, gobj::MoveParamFall fall, int a)
    : _0(speed), _8(decel), _C(fall), _18(a) {}

}}}}  // namespace scn::step::boss::common
