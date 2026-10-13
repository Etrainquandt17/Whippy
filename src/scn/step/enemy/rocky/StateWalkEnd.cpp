#include "scn/step/enemy/rocky/StateWalkEnd.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/rocky/ParamData.h"
#include "scn/step/enemy/rocky/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace rocky {

StateWalkEnd::StateWalkEnd(Enemy* enemy) : StateBase(enemy) {
    obj().model().reqScript(8);
    obj().model().anim().setFrameRate(1.0f);
    obj().move().resetSpeedH();
}

StateWalkEnd::~StateWalkEnd() {}

void StateWalkEnd::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateWalkEnd::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}
}
}
}
