#include "scn/step/boss/common/StateJumpAttackDesc.h"

#include "mintglue/VectorInline.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

StateJumpAttackDesc::StateJumpAttackDesc(hel::math::Vector2 speed, gobj::MoveParamDecel decel, gobj::MoveParamFall fall, int a)
    : _0(speed), _8(decel), _C(fall), _18(a) {}

}
}
}
}
