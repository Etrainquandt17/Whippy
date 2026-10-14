#include "scn/step/boss/doubter/StateEtherJumpStart.h"

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

StateEtherJumpStart::StateEtherJumpStart(Boss* boss, u32 count) : StateBase(boss), mCount(count) {
    obj().footState().setGround();
    obj().guard().setType(static_cast<GuardType>(2));
    obj().model().reqScript(32);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
}

StateEtherJumpStart::~StateEtherJumpStart() {}

void StateEtherJumpStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateEtherJumpRise, Boss*, u32>(objPtr(), mCount);
    }
}

void StateEtherJumpStart::procMove() {
    const Param& param = obj().param().doubter();
    obj().move().groundDecel(param._10);
}

void StateEtherJumpStart::procFixPos() {}

}}}}  // namespace scn::step::boss::doubter
