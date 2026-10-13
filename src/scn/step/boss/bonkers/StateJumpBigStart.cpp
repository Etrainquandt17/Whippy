#include "scn/step/boss/bonkers/StateJumpBigStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/bonkers/Param.h"
#include "scn/step/boss/bonkers/StateJumpBig.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

StateJumpBigStart::StateJumpBigStart(Boss* boss) : StateBase(boss) {
    obj().footState().setGround();
    obj().model().reqScript(9);
}

StateJumpBigStart::~StateJumpBigStart() {}

void StateJumpBigStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateJumpBig, Boss*>(objPtr());
    }
}

void StateJumpBigStart::procMove() {
    obj().move().groundDecel(obj().param().bonkers()._24);
}

void StateJumpBigStart::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

}}}}  // namespace scn::step::boss::bonkers
