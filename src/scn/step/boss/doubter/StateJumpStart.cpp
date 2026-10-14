#include "scn/step/boss/doubter/StateJumpStart.h"

#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/boss/doubter/StateJump.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateJumpStart::StateJumpStart(Boss* boss, const Vector2& speed, u32 count) : StateBase(boss), mSpeed(speed), mCount(count) {
    obj().model().reqScript(9);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
}

StateJumpStart::~StateJumpStart() {}

void StateJumpStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateJump, Boss*, Vector2, u32>(objPtr(), mSpeed, mCount);
    }
}

void StateJumpStart::procMove() {
    const Param& param = obj().param().doubter();
    obj().move().groundDecel(param._10);
}

void StateJumpStart::procFixPos() {}

}}}}  // namespace scn::step::boss::doubter
