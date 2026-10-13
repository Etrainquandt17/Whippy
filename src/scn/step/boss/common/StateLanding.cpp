#include "scn/step/boss/common/StateLanding.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

StateLanding::StateLanding(Boss* boss) : StateBase(boss) {
    init();
    obj().model().reqScript(2);
}

StateLanding::StateLanding(Boss* boss, int scriptKind) : StateBase(boss) {
    init();
    obj().model().reqScript(scriptKind);
}

StateLanding::~StateLanding() {}

void StateLanding::init() {
    obj().footState().setGround();
    obj().move().resetVelocity();
}

void StateLanding::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateLanding::procMove() {
    obj().move().groundDecel(gobj::MoveParamDecel::Create(0.01f));
}

void StateLanding::procFixPos() {
    StateFall::TryToChangeState(objPtr());
}

}
}
}
}
