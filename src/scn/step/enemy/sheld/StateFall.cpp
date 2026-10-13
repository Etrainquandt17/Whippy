#include "scn/step/enemy/sheld/StateFall.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateLanding.h"
#include "scn/step/enemy/sheld/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace sheld {

StateFall::StateFall(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(1);
    obj().move().resetSpeedV();
    f32 speed = obj().param().sheld().mJumpSpeedH * (obj().target().isRightDir() ? 1.0f : -1.0f);
    obj().move().setSpeedH(speed);
}

StateFall::~StateFall() {}

void StateFall::procAnim() {}

void StateFall::procMove() {
    obj().move().airDecelFall(obj().param().sheld().mFallDecel, obj().param().sheld().mFall);
}

void StateFall::procFixPos() {
    if (obj().mapColl().result()._2) {
        obj().move().resetSpeedH();
    }
    if (obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateLanding, Enemy*>(objPtr());
    }
}

}
}
}
}
