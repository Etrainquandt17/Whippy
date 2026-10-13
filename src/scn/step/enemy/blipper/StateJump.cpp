#include "scn/step/enemy/blipper/StateJump.h"

#include "app/Random.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/blipper/ParamData.h"
#include "scn/step/enemy/blipper/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace blipper {

StateJump::StateJump(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    const ParamData& param = obj().param().blipper();
    obj().footState().setAir();
    obj().model().reqScript(0);
    switch (app::Random::Rand(5)) {
    case 0:
    case 1:
        obj().move().setSpeedV(param.mJumpSpeedV[0]);
        break;
    case 2:
    case 3:
        obj().move().setSpeedV(param.mJumpSpeedV[1]);
        break;
    default:
        obj().move().setSpeedV(param.mJumpSpeedV[2]);
        break;
    }
    switch (app::Random::Rand(5)) {
    case 0:
    case 1:
    case 2:
    case 3:
        obj().move().setSpeedH(0.0f);
        break;
    default: {
        f32 dir = app::Random::Rand(2) == 0 ? 1.0f : -1.0f;
        obj().move().setSpeedH(param.mJumpSpeedH * dir);
        break;
    }
    }
    obj().target().setIsRightDir(app::Random::Rand(2) == 0);
}

void StateJump::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

void StateJump::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(0.0001f), gobj::MoveParamFall::Create(0.2f, 0.006f, 0.005f));
}

void StateJump::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}
}
}
}
