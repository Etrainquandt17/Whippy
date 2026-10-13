#include "scn/step/boss/kingsdoo/StateJumpMachinegunStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/kingsdoo/Param.h"
#include "scn/step/boss/kingsdoo/StateJumpMachinegun.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace kingsdoo {

StateJumpMachinegunStart::StateJumpMachinegunStart(Boss* boss) : StateBase(boss) {
    obj().footState().setGround();
    obj().model().reqScript(15);
    Utility::ControlHateOnAction(obj());
}

StateJumpMachinegunStart::~StateJumpMachinegunStart() {}

void StateJumpMachinegunStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateJumpMachinegun, Boss*>(objPtr());
    }
}

void StateJumpMachinegunStart::procMove() {
    const Param& param = obj().param().kingsdoo();
    obj().move().groundDecel(param._24);
}

void StateJumpMachinegunStart::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

}
}
}
}
