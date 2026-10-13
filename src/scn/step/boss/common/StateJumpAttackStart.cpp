#include "scn/step/boss/common/StateJumpAttackStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "mintglue/VectorInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/common/StateJumpAttack.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

StateJumpAttackStart::StateJumpAttackStart(Boss* boss, StateJumpAttackDesc& desc, unsigned long scriptKind0, unsigned long scriptKind1)
    : StateBase(boss), mScriptKind(scriptKind1), mDesc(desc) {
    obj().footState().setGround();
    obj().model().reqScript(scriptKind0);
    Utility::ControlHateOnAction(obj());
}

StateJumpAttackStart::~StateJumpAttackStart() {}

void StateJumpAttackStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateJumpAttack, Boss*, StateJumpAttackDesc, unsigned long>(objPtr(), mDesc, mScriptKind);
    }
}

void StateJumpAttackStart::procMove() {
    obj().move().groundDecel(gobj::MoveParamDecel::Create(0.01f));
}

void StateJumpAttackStart::procFixPos() {
    StateFall::TryToChangeState(objPtr());
}

}
}
}
}
