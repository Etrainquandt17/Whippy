#include "scn/step/boss/common/StateMoveForward.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

StateMoveForward::StateMoveForward(Boss* boss, StateMoveDesc desc, unsigned long scriptKind) : StateBase(boss), mDesc(desc) {
    obj().footState().setGround();
    obj().model().reqScript(scriptKind);
    obj().brainCtrl().toValid();
}

StateMoveForward::~StateMoveForward() {}

void StateMoveForward::procAnim() {}

void StateMoveForward::procMove() {
    obj().move().groundAccel(obj().target().isRightDir(), mDesc._0);
}

void StateMoveForward::procFixPos() {
    StateFall::TryToChangeState(objPtr());
}

}
}
}
}
