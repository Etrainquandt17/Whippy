#include "scn/step/boss/zankibble/StateJumpAttackStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/zankibble/Param.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace zankibble {

StateJumpAttackStart::StateJumpAttackStart(Boss* boss, StateJumpAttack::Config config) : StateBase(boss), mConfig(config) {
    obj().footState().setGround();
    obj().model().reqScript(17);
    Utility::ControlHateOnAction(obj());
}

StateJumpAttackStart::~StateJumpAttackStart() {}

void StateJumpAttackStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateJumpAttack, Boss*, StateJumpAttack::Config>(objPtr(), mConfig);
    }
}

void StateJumpAttackStart::procMove() {
    const Param& param = obj().param().zankibble();
    obj().move().groundDecel(param._24);
}

void StateJumpAttackStart::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

}
}
}
}
