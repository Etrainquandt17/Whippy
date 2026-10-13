#include "scn/step/boss/common/StateJump.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "mintglue/VectorInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

StateJumpStart::StateJumpStart(Boss* boss, StateJumpDesc& desc, u32 scriptKind0, u32 scriptKind1)
    : StateBase(boss), mScriptKind(scriptKind1), mDesc(desc) {
    obj().footState().setGround();
    obj().model().reqScript(scriptKind0);
}

StateJumpStart::~StateJumpStart() {}

void StateJumpStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateJump, Boss*, StateJumpDesc, unsigned long>(objPtr(), mDesc, mScriptKind);
    }
}

void StateJumpStart::procMove() {
    obj().move().groundDecel(mDesc._8);
}

void StateJumpStart::procFixPos() {
    StateFall::TryToChangeState(objPtr());
}

}
}
}
}
