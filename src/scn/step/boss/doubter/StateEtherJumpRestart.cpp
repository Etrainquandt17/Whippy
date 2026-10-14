#include "scn/step/boss/doubter/StateEtherJumpRestart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/boss/doubter/StateEtherJumpRise.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateEtherJumpRestart::StateEtherJumpRestart(Boss* boss, u32 count) : StateBase(boss), mCount(count) {
    obj().footState().setGround();
    obj().guard().setType(static_cast<GuardType>(2));
    obj().model().reqScript(35);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_3);
}

StateEtherJumpRestart::~StateEtherJumpRestart() {}

void StateEtherJumpRestart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateEtherJumpRise, Boss*, u32>(objPtr(), mCount);
    }
}

void StateEtherJumpRestart::procMove() {
    const Param& param = obj().param().doubter();
    obj().move().groundDecel(param._10);
}

void StateEtherJumpRestart::procFixPos() {}

}}}}  // namespace scn::step::boss::doubter
