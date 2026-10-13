#include "scn/step/enemy/tsukikage/StateWait.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/tsukikage/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    if (obj().dirType() == static_cast<map::BinEnemyDirType>(3)) {
        obj().model().reqScript(14);
    } else {
        obj().model().reqScript(0);
    }
    obj().brainCtrl().toValid();
}

StateWait::~StateWait() {}

void StateWait::procMove() {
    obj().move().groundDecel(obj().param().common().mDecel);
}

void StateWait::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}
}
}
}
