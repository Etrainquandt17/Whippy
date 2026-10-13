#include "scn/step/boss/common/StateFall.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/common/StateLanding.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

bool StateFall::TryToChangeState(Boss* boss) {
    if (!boss->mapColl().result().mIsHitFloor) {
        boss->stateChanger().setNextState<StateFall, Boss*>(boss);
        return true;
    }
    return false;
}

StateFall::StateFall(Boss* boss) : StateBase(boss) {
    obj().footState().setAir();
    obj().model().reqScript(3);
}

StateFall::~StateFall() {}

void StateFall::procAnim() {}

void StateFall::procMove() {
    const gobj::MoveParamDecel& decel = gobj::MoveParamDecel::Create(0.01f);
    gobj::MoveParamFall fall = gobj::MoveParamFall::Create(0.2f, 0.005f, 0.05f);
    obj().move().airDecelFall(decel, fall);
}

void StateFall::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateLanding, Boss*>(objPtr());
    }
}

}
}
}
}
