#include "scn/step/boss/bonkers/StateSwingEnd.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/bonkers/Param.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

StateSwingEnd::StateSwingEnd(Boss* boss) : StateBase(boss) {
    obj().footState().setGround();
    obj().model().reqScript(12);
}

StateSwingEnd::~StateSwingEnd() {}

void StateSwingEnd::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateWait, Boss*>(objPtr());
    }
}

void StateSwingEnd::procMove() {
    obj().move().groundDecel(obj().param().bonkers()._B4);
}

void StateSwingEnd::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

}}}}  // namespace scn::step::boss::bonkers
