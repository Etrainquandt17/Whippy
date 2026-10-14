#include "scn/step/boss/moundeath/StateRollingEnd.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/boss/moundeath/Param.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

StateRollingEnd::StateRollingEnd(Boss* boss) : StateBase(boss) {
    obj().footState().setGround();
    obj().model().reqScript(0x19);
}

StateRollingEnd::~StateRollingEnd() {}

void StateRollingEnd::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateWait, Boss*>(objPtr());
    }
}

void StateRollingEnd::procMove() {
    const Param& param = obj().param().moundeath();
    obj().move().groundDecel(param._138);
}

void StateRollingEnd::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

}}}}  // namespace scn::step::boss::moundeath
