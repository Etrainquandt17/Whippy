#include "scn/step/enemy/bladeknight/StateWalk.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/common/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace bladeknight {

StateWalk::StateWalk(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(3);
    obj().brainCtrl().toValid();
}

StateWalk::~StateWalk() {}

void StateWalk::procAnim() {}

void StateWalk::procMove() {
    const gobj::MoveParamAccel& accel = gobj::MoveParamAccel::Create(0.03f, 0.003f, 0.003f);
    obj().move().groundAccel(obj().target().isRightDir(), accel);
}

void StateWalk::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result._2) {
        obj().move().resetSpeedH();
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}
}
}
}
