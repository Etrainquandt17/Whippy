#include "scn/step/boss/watergalboros/StateAttackJoint.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/boss/watergalboros/Param.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace watergalboros {

StateAttackJoint::StateAttackJoint(Boss* boss, u32 scriptKind) : StateBase(boss) {
    obj().footState().setGround();
    obj().model().reqScript(scriptKind);
}

StateAttackJoint::~StateAttackJoint() {}

void StateAttackJoint::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateWait, Boss*>(objPtr());
    }
}

void StateAttackJoint::procMove() {
    const Param& param = obj().param().watergalboros();
    obj().move().groundDecel(param._24);
}

void StateAttackJoint::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

}}}}  // namespace scn::step::boss::watergalboros
