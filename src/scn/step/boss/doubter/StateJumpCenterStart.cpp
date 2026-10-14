#include "scn/step/boss/doubter/StateJumpCenterStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/boss/doubter/StateJumpCenter.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateJumpCenterStart::StateJumpCenterStart(Boss* boss, f32 speed, u32 kind) : StateBase(boss), mSpeed(speed), mKind(kind) {
    obj().footState().setGround();
    obj().model().reqScript(9);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
}

StateJumpCenterStart::~StateJumpCenterStart() {}

void StateJumpCenterStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateJumpCenter, Boss*, f32, u32>(objPtr(), mSpeed, mKind);
    }
}

void StateJumpCenterStart::procMove() {
    const Param& param = obj().param().doubter();
    obj().move().groundDecel(param._10);
}

void StateJumpCenterStart::procFixPos() {}

}}}}  // namespace scn::step::boss::doubter
